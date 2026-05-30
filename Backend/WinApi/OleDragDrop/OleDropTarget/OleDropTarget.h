#pragma once

#include <cstdint>
#include <functional>
#include <oleidl.h>
#include <shobjidl.h>
#include <vector>

#include "Common/Types.h"
#include "WinApi/Router/CommandRouter/CommandRouter.h"

namespace Blade::Backend {

class OleDropTarget : public IDropTarget
{
public:
    using TargetResolver = std::function<Api::Id(POINT screenPoint)>;
    using DragLeaveHandler = std::function<void()>;

    OleDropTarget(Api::Id id, CommandRouter& router);
    ~OleDropTarget();

    auto registerHwnd(HWND hwnd) -> bool;
    auto setTargetResolver(TargetResolver resolver) -> void;
    auto setDragLeaveHandler(DragLeaveHandler handler) -> void;

    auto QueryInterface(REFIID iid, void** object) -> HRESULT override;
    auto AddRef() -> ULONG override;
    auto Release() -> ULONG override;

    auto DragEnter(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT override;
    auto DragOver(DWORD keyState, POINTL point, DWORD* effect) -> HRESULT override;
    auto DragLeave() -> HRESULT override;
    auto Drop(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT override;

private:
    static auto HasFiles(IDataObject* data) -> bool;
    static auto ReadFiles(IDataObject* data, Api::Id id) -> Api::Text;
    static auto ApplyEffect(DWORD* effect, bool allow) -> DWORD;
    static auto ToPoint(POINTL point) -> POINT;

private:
    LONG m_refs = 1;
    std::vector<std::uintptr_t> m_hwnds;
    Api::Id m_id = Api::InvalidId;
    bool m_allowDrop = false;
    CommandRouter& m_router;
    TargetResolver m_targetResolver;
    DragLeaveHandler m_dragLeaveHandler;
    IDropTargetHelper* m_helper = nullptr;
};

} // namespace Blade::Backend
