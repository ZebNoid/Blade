#pragma once

#include <optional>
#include <memory>
#include <shellapi.h>

#include "WinApi/Menu/NativeContextMenu/NativeContextMenu.h"
#include "WinApi/NativeElement/NativeElement.h"
#include "WinApi/Router/CommandRouter/CommandRouter.h"

namespace Blade::Backend {

class NativeTray : public NativeElement
{
public:
    ~NativeTray() override;

    auto create(HINSTANCE hInstance, Api::Id id, Api::BackendMessageHandler* handler) -> bool;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;
    auto applyEvents(const Api::EventSubscriptions& events) -> void override;
    auto destroy() -> void override;
    auto isAlive() const -> bool override;
    auto attachChild(INativeElement* child) -> void override;
    auto setIcon(const Api::Text& path) -> void;
    auto setTitle(const Api::Text& title) -> void;

private:
    static auto CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR id, DWORD_PTR data) -> LRESULT;
    auto handle(UINT msg, WPARAM wParam, LPARAM lParam) -> std::optional<LRESULT>;

    auto updateContextMenus(const Api::ContextMenus& menus) -> void;
    auto updateLifetime(Api::Lifetime lifetime) -> void;
    auto notify(DWORD message) -> bool;

private:
    bool m_alive = true;
    NOTIFYICONDATAW m_data{};
    HICON m_icon = nullptr;
    CommandRouter m_commandRouter;
    std::unique_ptr<NativeContextMenu> m_contextMenu;
};

} // namespace Blade::Backend
