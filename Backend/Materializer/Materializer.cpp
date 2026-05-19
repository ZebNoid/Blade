#include "Materializer.h"

#include "Widget/WinButton/WinButton.h"
#include "Widget/WinLabel/WinLabel.h"
#include "Widget/WinNop/WinNop.h"
#include "Widgets/Button/Button.h"
#include "Widgets/Label/Label.h"
#include "Widgets/Nop/Nop.h"
#include "Windows/Window/Window.h"
#include "WinWindow/WinWindow.h"


namespace Blade::Backend {


auto Materializer::create(Widget& widget) -> std::unique_ptr<ApiWidget>
{
    // std::cout << "Materializer::create " << Utf16ToUtf8(widget.name()) << "\n"; // TODO dev

    if (auto* window = dynamic_cast<Window*>(&widget))
    {
        return std::make_unique<WinWindow>(*window);
    }

    if (auto* label = dynamic_cast<Label*>(&widget))
    {
        return std::make_unique<WinLabel>(*label);
    }

    if (auto* button = dynamic_cast<Button*>(&widget))
    {
        return std::make_unique<WinButton>(*button);
    }

    if (auto* nop = dynamic_cast<Nop*>(&widget))
    {
        return std::make_unique<WinNop>(*nop);
    }

    return std::make_unique<WinNop>(L"Unknown " + widget.name());;
}

auto Materializer::mount(Widget& widget) -> std::unique_ptr<ApiWidget>
{
    auto native = create(widget);
    buildChildren(widget, *native);
    return native;
}

auto Materializer::buildChildren(Widget& widget, ApiWidget& native) -> void
{
    // std::cout << "Materializer::buildChildren " << widget.children().size() << "\n"; // TODO dev
    for (auto& child : widget.children())
    {
        auto nativeChild = create(*child);

        nativeChild->create(native);

        native.addChild(
            std::move(nativeChild)
        );
    }
}


} // namespace
