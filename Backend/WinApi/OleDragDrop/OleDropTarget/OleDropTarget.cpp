#include "OleDropTarget.h"

#include <shlobj.h>
#include <shellapi.h>

#include "Common/Logger.h"

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

    const auto result = RegisterDragDrop(hwnd, this);
    if (FAILED(result))
    {
        LOGF_E(L"[Error] OleDropTarget::RegisterDragDrop failed [%08X]", static_cast<unsigned>(result));
        return false;
    }

    m_hwnds.push_back(reinterpret_cast<std::uintptr_t>(hwnd));
    LOGF_D(L"OleDropTarget::RegisterDragDrop [%p]", hwnd);
    return true;
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
    SetCopyEffect(effect, m_allowDrop);

    auto pt = this->point(point);
    if (m_helper) m_helper->DragEnter(nullptr, data, &pt, *effect);
    return S_OK;
}

auto OleDropTarget::DragOver(DWORD keyState, POINTL point, DWORD* effect) -> HRESULT
{
    SetCopyEffect(effect, m_allowDrop);
    auto pt = this->point(point);
    if (m_helper) m_helper->DragOver(&pt, *effect);
    return S_OK;
}

auto OleDropTarget::DragLeave() -> HRESULT
{
    m_allowDrop = false;
    if (m_helper) m_helper->DragLeave();
    return S_OK;
}

auto OleDropTarget::Drop(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT
{
    const auto files = ReadFiles(data);
    SetCopyEffect(effect, !files.empty());
    m_allowDrop = false;
    auto pt = this->point(point);
    if (m_helper) m_helper->Drop(data, &pt, *effect);

    if (!files.empty())
    {
        m_router.emit({
            .target = m_id,
            .type = Api::Events::Drop,
            .payload = files
        });
    }

    return S_OK;
}

auto OleDropTarget::HasFiles(IDataObject* data) -> bool
{
    if (!data) return false;

    auto format = FileFormat();
    return data->QueryGetData(&format) == S_OK;
}

auto OleDropTarget::ReadFiles(IDataObject* data) -> Api::Text
{
    if (!data) return {};

    auto format = FileFormat();
    STGMEDIUM storage{};

    const auto getDataResult = data->GetData(&format, &storage);
    if (FAILED(getDataResult))
    {
        LOGF_E(L"[Error] OleDropTarget::GetData failed [%08X]", static_cast<unsigned>(getDataResult));
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

auto OleDropTarget::SetCopyEffect(DWORD* effect, bool allow) -> void
{
    if (effect) *effect = allow ? DROPEFFECT_COPY : DROPEFFECT_NONE;
}

auto OleDropTarget::point(POINTL point) const -> POINT
{
    return {
        .x = point.x,
        .y = point.y
    };
}

} // namespace Blade::Backend
