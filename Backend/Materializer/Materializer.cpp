#include "Materializer.h"

#include "Widget/WinButton/WinButton.h"
#include "Widget/WinNop/WinNop.h"
#include "Widgets/Button/Button.h"
#include "Widgets/Nop/Nop.h"
#include "Windows/Window/Window.h"
#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


auto Materializer::create(Widget& widget) -> std::unique_ptr<WinWidget>
{
    std::cout << "Materializer::create\n"; // TODO dev

    if (auto* window = dynamic_cast<Window*>(&widget))
    {
        return std::make_unique<WinWindow>(
            *window
        );
    }

    // if (auto* button = dynamic_cast<Button*>(&widget))
    // {
    //     return std::make_unique<WinButton>(
    //         *button
    //     );
    // }

    if (auto* nop = dynamic_cast<Nop*>(&widget))
    {
        return std::make_unique<WinNop>(
            L"Nop"
            // *nop
        );
    }

    auto unknown =  std::make_unique<WinNop>(L"Unknown " + widget.name());
    return unknown;
}

auto Materializer::mount(Widget& root) -> std::unique_ptr<ApiWidget>
{
    return create(root);
}


} // namespace
