#pragma once


using WidgetId = uint32_t;

struct Point
{
    int x;
    int y;
};


struct Rect
{
    int x{};
    int y{};
    int width{};
    int height{};
};

// TODO to separate file
#define NAME_OF(__any__) #__any__
