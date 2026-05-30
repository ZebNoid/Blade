#pragma once

namespace Blade::Api {

struct Color
{
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 255;

    static auto Transparent() -> Color { return {0, 0, 0, 0}; }
    static auto Black() -> Color { return {0, 0, 0, 255}; }
    static auto White() -> Color { return {255, 255, 255, 255}; }
    static auto Red() -> Color { return {255, 0, 0, 255}; }
    static auto Green() -> Color { return {0, 128, 0, 255}; }
    static auto Blue() -> Color { return {0, 0, 255, 255}; }
};

} // namespace Blade::Api
