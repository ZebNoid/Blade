#pragma once

#include <cstdint>
#include <oleidl.h>
#include <shobjidl.h>
#include <vector>

#include "Common/Types.h"
#include "WinApi/Router/CommandRouter/CommandRouter.h"

namespace Blade::Backend {

class OleDropTarget : public IDropTarget
{
public:
    OleDropTarget(Api::Id id, CommandRouter& router);
    ~OleDropTarget();

    auto registerHwnd(HWND hwnd) -> bool;

    auto QueryInterface(REFIID iid, void** object) -> HRESULT override;
    auto AddRef() -> ULONG override;
    auto Release() -> ULONG override;

    auto DragEnter(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT override;
    auto DragOver(DWORD keyState, POINTL point, DWORD* effect) -> HRESULT override;
    auto DragLeave() -> HRESULT override;
    auto Drop(IDataObject* data, DWORD keyState, POINTL point, DWORD* effect) -> HRESULT override;

private:
    static auto HasFiles(IDataObject* data) -> bool;
    static auto ReadFiles(IDataObject* data) -> Api::Text;
    static auto SetCopyEffect(DWORD* effect, bool allow) -> void;
    auto point(POINTL point) const -> POINT;

private:
    LONG m_refs = 1;
    std::vector<std::uintptr_t> m_hwnds;
    Api::Id m_id = Api::InvalidId;
    bool m_allowDrop = false;
    CommandRouter& m_router;
    IDropTargetHelper* m_helper = nullptr;
};

} // namespace Blade::Backend
