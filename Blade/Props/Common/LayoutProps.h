#pragma once

struct Thickness
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
};

struct LayoutProps
{
    Thickness margin{};
    Thickness padding{};
};