#include "OleDropTarget.h"

#include <shlobj.h>
#include <shellapi.h>

#include "Logging/Logger.h"

namespace Blade::Backend {

namespace {

auto FileFormat() -> FORMATETC
{
    return {
        .cfFormat = CF_HDROP,
        .ptd = nullptr,
        .dwAspect = DVASPECT_CONTENT,
        .lindex = -1,
        .tymed = TYMED_HGLOBAL
    };
}

auto HandleValue(HWND hwnd) -> std::uintptr_t
{
    return reinterpret_cast<std::uintptr_t>(hwnd);
}

auto Contains(const std::vector<std::uintptr_t>& handles, HWND hwnd) -> bool
{
    const auto value = HandleValue(hwnd);

    for (const auto handle : handles)
    {
        if (handle == value) return true;
    }

    return false;
}

} // namespace

OleDropTarget::OleDropTarget(Api::Id id, CommandRouter& router)
    : m_id(id)
    , m_router(router)
{
    CoCreateInstance(CLSID_DragDropHelper, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_helper));
}

OleDropTarget::~OleDropTarget()
{
    for (const auto hwnd : m_hwnds) RevokeDragDrop(reinterpret_cast<HWND>(hwnd));
    if (m_helper) m_helper->Release();
}

auto OleDropTarget::registerHwnd(HWND hwnd) -> bool
{
    if (!hwnd) return false;
    if (Contains(m_hwnds, hwnd)) return true;

    const auto result = RegisterDragDrop(hwnd, this);
    if (FAILED(result))
    {
        LOGF_E(L"[Error] OleDropTarget::RegisterDragDrop failed id=%d hwnd=%p [%08X]", m_id, hwnd, static_cast<unsigned>(result));
        return false;
    }

    m_hwnds.push_back(HandleValue(hwnd));
    LOGF_D(L"OleDropTarget::RegisterDragDrop id=%d hwnd=%p", m_id, hwnd);
    return true;
}

auto OleDropTarget::setTargetResolver(TargetResolver resolver) -> void
{
    m_targetResolver = std::move(resolver);
}

auto OleDropTarget::setDragLeaveHandler(DragLeaveHandler handler) -> void
{
    m_dragLeaveHandler = std::move(handler);
}

auto OleDropTarget::QueryInterface(REFIID iid, void** object) -> HRESULT
{
    if (!object) return E_POINTER;

    if (iid == IID_IUnknown || iid == IID_IDropTarget)
    {
        *object = static_cast<IDropTarget*>(this);
        AddRef();
        return S_OK;
    }

    *object = nullptr;
    return E_NOINTERFACE;
}

auto OleDropTarget::AddRef() -> ULONG
{
    return InterlockedIncrement(&m_refs);
}

auto OleDropTarget::Release() -> ULONG
{
    const auto refs = InterlockedDecrement(&m_refs);
    if (refs == 0) delete this;
    return refs;
}

auto OleDropTarget::DragEnter(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT
{
    m_allowDrop = HasFiles(data);
    const auto dropEffect = ApplyEffect(effect, m_allowDrop);

    auto pt = ToPoint(point);
    if (m_helper) m_helper->DragEnter(nullptr, data, &pt, dropEffect);
    return S_OK;
}

auto OleDropTarget::DragOver(DWORD keyState, POINTL point, DWORD* effect) -> HRESULT
{
    const auto dropEffect = ApplyEffect(effect, m_allowDrop);

    auto pt = ToPoint(point);
    if (m_allowDrop && m_targetResolver) m_targetResolver(pt);
    if (m_helper) m_helper->DragOver(&pt, dropEffect);
    return S_OK;
}

auto OleDropTarget::DragLeave() -> HRESULT
{
    m_allowDrop = false;
    if (m_dragLeaveHandler) m_dragLeaveHandler();
    if (m_helper) m_helper->DragLeave();
    return S_OK;
}

auto OleDropTarget::Drop(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT
{
    const auto files = ReadFiles(data, m_id);
    const auto dropEffect = ApplyEffect(effect, !files.empty());
    m_allowDrop = false;
    auto pt = ToPoint(point);
    if (m_helper) m_helper->Drop(data, &pt, dropEffect);

    if (!files.empty())
    {
        const auto target = m_targetResolver ? m_targetResolver(pt) : m_id;
        m_router.emit({
            .target = target == Api::InvalidId ? m_id : target,
            .type = Api::Events::Drop,
            .payload = files
        });
    }

    if (m_dragLeaveHandler) m_dragLeaveHandler();
    return S_OK;
}

auto OleDropTarget::HasFiles(IDataObject* data) -> bool
{
    if (!data) return false;

    auto format = FileFormat();
    return data->QueryGetData(&format) == S_OK;
}

auto OleDropTarget::ReadFiles(IDataObject* data, Api::Id id) -> Api::Text
{
    if (!data) return {};

    auto format = FileFormat();
    STGMEDIUM storage{};

    const auto getDataResult = data->GetData(&format, &storage);
    if (FAILED(getDataResult))
    {
        LOGF_E(L"[Error] OleDropTarget::GetData failed id=%d [%08X]", id, static_cast<unsigned>(getDataResult));
        return {};
    }

    const auto drop = static_cast<HDROP>(storage.hGlobal);
    Api::Text result;

    if (drop)
    {
        const auto count = DragQueryFileW(drop, 0xFFFFFFFF, nullptr, 0);

        for (UINT i = 0; i < count; ++i)
        {
            const auto length = DragQueryFileW(drop, i, nullptr, 0);
            Api::Text path(length + 1, L'\0');
            DragQueryFileW(drop, i, path.data(), length + 1);
            path.resize(length);

            if (!result.empty()) result += L"\n";
            result += path;
        }
    }

    ReleaseStgMedium(&storage);
    return result;
}

auto OleDropTarget::ApplyEffect(DWORD* effect, bool allow) -> DWORD
{
    const auto value = allow ? DROPEFFECT_COPY : DROPEFFECT_NONE;
    if (effect) *effect = value;
    return value;
}

auto OleDropTarget::ToPoint(POINTL point) -> POINT
{
    return {
        .x = point.x,
        .y = point.y
    };
}

} // namespace Blade::Backend
