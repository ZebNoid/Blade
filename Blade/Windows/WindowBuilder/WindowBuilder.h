#pragma once

#include <memory>

#include "WidgetsProps/Window/WindowProps.h"
#include "Widgets/Widget/Widget.h"
#include "WidgetsEvents/Window/WindowEvents.h"


namespace Blade {


class WindowBuilder
{
public:
    template <typename T>
    WindowBuilder(T&& root)
    {
        using WidgetType = std::decay_t<T>;

        m_root = std::make_unique<WidgetType>( // оригинальная проблема
            std::forward<T>(root)
        );
    }

    auto set(WindowProps props) -> WindowBuilder&
    {
        m_props = std::move(props);
        return *this;
    }

    auto on(WindowEvents events) -> WindowBuilder&
    {
        m_events = std::move(events);
        return *this;
    }

    auto id(WidgetId& id) -> WindowBuilder&
    {
        // TODO get id
        // id = m_id;
        return *this;
    }

    auto takeRoot() -> std::unique_ptr<Widget>
    {
        return std::move(m_root);
    }

private:
    WindowProps m_props;
    WindowEvents m_events;
    std::unique_ptr<Widget> m_root;

    friend class WindowManager;
};


} // namespace
