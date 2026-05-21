#pragma once
#include "Common/Property.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {


class NativePropertyMapper
{
public:
    static auto apply(
        NativeNode& node,
        const Api::PropertyMap& props
    ) -> void;
};


} // namespace
