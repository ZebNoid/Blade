#pragma once
#include <memory>

#include "Props/Window/WindowProps.h"
#include "Widgets/Widget/Widget.h"


class WindowBuilder
{
public:
    auto set(WindowProps props) -> WindowBuilder&;

private:
    WindowProps m_props;
    std::unique_ptr<Widget> m_root;
};
