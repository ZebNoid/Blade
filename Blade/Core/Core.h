#pragma once


using WidgetId = uint32_t;



struct Rect
{
    int x{};
    int y{};
    int width{};
    int height{};
};

// TODO remove? to separate file
#define NAME_OF(__any__) #__any__
