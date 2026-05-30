#pragma once

#include "Base/RootWidget.h"
#include "Lifecycle/Lifetime.h"

namespace Blade {

class Tray : public RootWidget<Tray>
{
public:
    Tray()
    {
        m_tree.type = Api::WidgetTypes::Tray;
        initDefaults();
    }

    template <typename... TMenus>
    explicit Tray(TMenus&&... menus)
    {
        m_tree.type = Api::WidgetTypes::Tray;
        initDefaults();

        (
            m_tree.overlays.push_back(menus.tree()),
            ...
        );
    }

    auto title(Api::Text title) -> Tray&
    {
        m_tree.backend.create[Api::Props::Title] = std::move(title);
        return *this;
    }

    auto icon(Api::Text icon) -> Tray&
    {
        m_tree.backend.create[Api::Props::Icon] = std::move(icon);
        return *this;
    }

    auto lifetime(Api::Lifetime lifetime) -> Tray&
    {
        m_tree.lifetime = lifetime;
        return *this;
    }

    auto onClick(Api::EventCallback callback) -> Tray&
    {
        applyEvent(Api::Events::Click, std::move(callback));
        return *this;
    }

private:
    auto initDefaults() -> void
    {
        title(L"Blade");
        icon({});
        lifetime(Api::Lifetime::Owner);
    }
};

} // namespace Blade
