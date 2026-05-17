#include "Stack.h"


namespace Blade {


auto Stack::measure(Size available) -> Size
{
    return {200,200};
}

void Stack::arrange(Rect rect)
{
    Container::arrange(rect);
}
} // namespace
