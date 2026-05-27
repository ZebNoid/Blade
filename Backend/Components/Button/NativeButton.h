#pragma once

#include <memory>

#include "WinApi/NativeElement/NativeElement.h"
#include "WinApi/OleDragDrop/OleDropTarget/OleDropTarget.h"


namespace Blade::Backend {

class NativeWindow;

class NativeButton : public NativeElement
{
public:
    auto create(NativeWindow* parent, Api::Id id) -> bool;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto applyEvents(const Api::EventSubscriptions& events) -> void override;
    auto enableDropTarget() -> void;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override
    {
    }

private:
    std::unique_ptr<OleDropTarget> m_dropTarget;
};


} // namespace
