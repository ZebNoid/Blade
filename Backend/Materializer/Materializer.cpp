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

    return nullptr;
    // if (auto* window = dynamic_cast<Window*>(&widget))
    // {
    //     return std::make_unique<WinWindow>(
    //         *window
    //     );
    // }
    //
    // if (auto* button = dynamic_cast<Button*>(&widget))
    // {
    //     return std::make_unique<WinButton>(
    //         *button
    //     );
    // }
    //
    // if (auto* nop = dynamic_cast<Nop*>(&widget))
    // {
    //     return std::make_unique<WinNop>(
    //         *nop
    //     );
    // }
    //
    // return std::make_unique<WinNop>(
    //     widget
    // );
}

auto Materializer::mount(Widget& root) -> WinWidget*
{
    // return create(root);
    return nullptr;
}


} // namespace
