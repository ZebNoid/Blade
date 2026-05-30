#pragma once

#include <algorithm>
#include <cmath>
#include <string_view>

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
    static auto DarkRed() -> Color { return {139, 0, 0, 255}; }
    static auto Gray() -> Color { return {128, 128, 128, 255}; }
    static auto Green() -> Color { return {0, 128, 0, 255}; }
    static auto Blue() -> Color { return {0, 0, 255, 255}; }
    static auto Yellow() -> Color { return {255, 255, 0, 255}; }

    static auto Hex(std::string_view value) -> Color
    {
        return HexValue(value);
    }

    static auto Hex(std::wstring_view value) -> Color
    {
        return HexValue(value);
    }

    static auto Hue(double hue, double saturation = 1.0, double value = 1.0, int alpha = 255) -> Color
    {
        hue = std::fmod(hue, 360.0);
        if (hue < 0.0) hue += 360.0;

        saturation = std::clamp(saturation, 0.0, 1.0);
        value = std::clamp(value, 0.0, 1.0);

        const double c = value * saturation;
        const double x = c * (1.0 - std::abs(std::fmod(hue / 60.0, 2.0) - 1.0));
        const double m = value - c;

        double r{};
        double g{};
        double b{};

        if (hue < 60.0) { r = c; g = x; }
        else if (hue < 120.0) { r = x; g = c; }
        else if (hue < 180.0) { g = c; b = x; }
        else if (hue < 240.0) { g = x; b = c; }
        else if (hue < 300.0) { r = x; b = c; }
        else { r = c; b = x; }

        return {
            Channel(r + m),
            Channel(g + m),
            Channel(b + m),
            std::clamp(alpha, 0, 255)
        };
    }

private:
    static auto Channel(double value) -> int
    {
        return std::clamp(static_cast<int>(std::round(value * 255.0)), 0, 255);
    }

    template <typename TText>
    static auto HexValue(TText value) -> Color
    {
        if (!value.empty() && value.front() == '#') value.remove_prefix(1);

        if (value.size() != 6 && value.size() != 8) return {};

        const int r = HexByte(value[0], value[1]);
        const int g = HexByte(value[2], value[3]);
        const int b = HexByte(value[4], value[5]);
        const int a = value.size() == 8 ? HexByte(value[6], value[7]) : 255;

        if (r < 0 || g < 0 || b < 0 || a < 0) return {};
        return {r, g, b, a};
    }

    template <typename TChar>
    static auto HexByte(TChar high, TChar low) -> int
    {
        const int h = HexDigit(high);
        const int l = HexDigit(low);
        if (h < 0 || l < 0) return -1;
        return h * 16 + l;
    }

    template <typename TChar>
    static auto HexDigit(TChar value) -> int
    {
        if (value >= '0' && value <= '9') return static_cast<int>(value - '0');
        if (value >= 'a' && value <= 'f') return static_cast<int>(value - 'a' + 10);
        if (value >= 'A' && value <= 'F') return static_cast<int>(value - 'A' + 10);
        return -1;
    }
};

} // namespace Blade::Api
