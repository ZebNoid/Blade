#pragma once

#include "Components/Custom/Surface/NativeCustom.h"

namespace Blade::Backend {

class NativeLabel : public NativeCustom
{
public:
    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

protected:
    auto onPaint(HDC hdc, const Api::Rect& rect) -> void override;
    auto exStyle() const -> DWORD override;
    auto hitTest() const -> LRESULT override;

private:
    Api::Text m_text;
};

} // namespace Blade::Backend
