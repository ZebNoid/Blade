#include "Materializer.h"

#include "Widget/WinButton/WinButton.h"
#include "Widgets/Button/Button.h"


namespace Blade::Backend {


auto Materializer::create(Widget& widget) -> std::unique_ptr<ApiWidget>
{
    if (auto* button = dynamic_cast<Button*>(&widget))
    {
        // return std::make_unique<WinButton>(*button);
    }
    return nullptr; // TODO Nop
}
} // namespace
