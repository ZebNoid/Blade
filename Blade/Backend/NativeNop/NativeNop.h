#pragma once
#include "Backend/NativeCustom/NativeCustom.h"


namespace Blade {


class NativeNop : public NativeCustom
{
protected:
    auto widgetName() const -> std::string override { return "NativeNop"; }
};


} // namespace
