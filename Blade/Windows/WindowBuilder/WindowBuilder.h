#pragma once
#include <memory>

#include "Props/Window/WindowProps.h"
#include "Widgets/Widget/Widget.h"


class WindowBuilder
{
public:
    template <typename T>
    WindowBuilder(T&& root)
    {
        using WidgetType = std::decay_t<T>;

        m_root = std::make_unique<WidgetType>(
            std::forward<T>(root)
        );
    }

    auto set(WindowProps props) -> WindowBuilder&
    {
        m_props = std::move(props);
        return *this;
    }


private:
    WindowProps m_props;
    std::unique_ptr<Widget> m_root;

    friend class WindowManager;
};
