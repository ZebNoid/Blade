#include "Materializer.h"

#include "Widget/WinButton/WinButton.h"
#include "Widget/WinNop/WinNop.h"
#include "Widgets/Button/Button.h"
#include "Widgets/Nop/Nop.h"
#include "Windows/Window/Window.h"
#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


auto Materializer::create(Widget& widget) -> std::unique_ptr<ApiWidget>
{
    std::cout << "Materializer::create\n"; // TODO dev

    if (auto* window = dynamic_cast<Window*>(&widget))
    {
        return std::make_unique<WinWindow>(*window);
    }

    // if (auto* button = dynamic_cast<Button*>(&widget))
    // {
    //     return std::make_unique<WinButton>(
    //         *button
    //     );
    // }

    if (auto* nop = dynamic_cast<Nop*>(&widget))
    {
        return std::make_unique<WinNop>(*nop);
    }

    return std::make_unique<WinNop>(L"Unknown " + widget.name());;
}

auto Materializer::mount(Widget& root) -> std::unique_ptr<ApiWidget>
{
    return create(root);
}

auto Materializer::buildChildren(Widget& widget, ApiWidget& native) -> void
{
    std::cout << "WinBackend::buildChildren " << widget.children().size() <<"\n"; // TODO dev
    for (auto& child : widget.children())
    {
        auto nativeChild = create(*child);

        nativeChild->create(native);

        buildChildren(
            *child,
            *nativeChild
        );

        native.addChild(
            std::move(nativeChild)
        );
    }
}


} // namespace
