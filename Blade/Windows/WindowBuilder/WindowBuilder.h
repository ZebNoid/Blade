#pragma once
#include <memory>

#include "Props/Window/WindowProps.h"
#include "Widgets/Widget/Widget.h"


class WindowBuilder
{
public:
    WindowBuilder(WindowBuilder&&) noexcept = default;
    auto operator=(WindowBuilder&&) noexcept -> WindowBuilder& = default;

    WindowBuilder(const WindowBuilder&) = delete;
    auto operator=(const WindowBuilder&) -> WindowBuilder& = delete;

public:
    template <typename T>
    WindowBuilder(T&& root)
    {
        using WidgetType = std::decay_t<T>;

        m_root = std::make_unique<WidgetType>( // проблема
            std::forward<T>(root)
        );
    }

    auto set(WindowProps props) -> WindowBuilder&
    {
        m_props = std::move(props);
        return *this;
    }

    auto takeRoot() -> std::unique_ptr<Widget>&
    {
        return m_root;
    }

private:
    WindowProps m_props;
    std::unique_ptr<Widget> m_root;

    friend class WindowManager;
};
