#pragma once



namespace Blade {


class LayoutTreeBuilder
{
public:
    static auto Build(
        const WidgetTree& tree
    ) -> LayoutNode;

private:
    static auto BuildNode(
        const WidgetTree& tree
    ) -> LayoutNode;

    static auto ExtractLayoutData(
        const Api::PropertyMap& props
    ) -> LayoutData;
};


} // namespace
