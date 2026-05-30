#pragma once

#include "Components/Label/NativeLabel/NativeLabel.h"

namespace Blade::Backend {

class NativeCustomButton : public NativeLabel
{
protected:
    auto hitTest() const -> LRESULT override;
};

} // namespace Blade::Backend
