#include "Materializer.h"

#include "Core/Encoding.h"
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

    return nullptr;

    std::cerr << "! Unknown Widget " << Utf16ToUtf8(widget.name()) << "\n"; // TODO dev
    return std::make_unique<WinNop>(L"Unknown " + widget.name());
}

auto Materializer::mount(Widget& widget) -> std::unique_ptr<ApiWidget>
{
    auto native = create(widget);
    if (!native)
    {
        return nullptr;
    }

    buildChildren(widget, *native);
    return native;
}

auto Materializer::buildChildren(Widget& widget, ApiWidget& nativeParent) -> void
{
    for (auto& child : widget.children())
    {
        auto childNative = create(*child);

        //
        // Native-backed widget
        //
        if (childNative)
        {
            auto* childNativePtr = childNative.get();
            buildChildren(*child, *childNativePtr);
            nativeParent.addChild(std::move(childNative));
        }
        //
        // Layout-only widget
        //
        else
        {
            buildChildren(*child, nativeParent);
        }
    }
}


} // namespace
