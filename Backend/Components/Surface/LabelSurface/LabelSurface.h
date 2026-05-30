#pragma once

#include "Components/RenderSurface/RenderSurface.h"

namespace Blade::Backend {

class LabelSurface : public RenderSurface
{
public:
    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;
    auto paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void override;

private:
    Api::Text m_text;
};

} // namespace Blade::Backend
