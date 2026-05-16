#include "Column.h"

#include "Layout/Flex/FlexLayout.h"


namespace Blade {

auto Column::measure(Size available) -> Size
{
    return FlexLayout::Measure(
        FlexDirection::Column,
        m_children,
        m_props.layout,
        m_props.gap,
        available
    );
}

auto Column::arrange(const Rect rect) -> void
{
    Widget::arrange(rect);

    return FlexLayout::Arrange(
        FlexDirection::Column,
        m_children,
        m_props.layout,
        m_props.mainAxisAlignment,
        m_props.crossAxisAlignment,
        m_props.gap,
        rect
    );
}

// auto Column::measure(const Size available) -> Size
// {
//     int totalHeight = 0;
//     int maxWidth = 0;
//
//     const int gap = m_props.gap;
//     bool first = true;
//
//     for (const auto& child : m_children)
//     {
//         Size childSize = child->measure(available);
//         const auto& margin = child->layout().margin;
//
//         // spacing between items
//         if (!first)
//         {
//             totalHeight += gap;
//         }
//         else
//         {
//             first = false;
//         }
//
//         totalHeight +=
//             margin.top +
//             childSize.height +
//             margin.bottom;
//
//         maxWidth = max(
//             maxWidth,
//             margin.left +
//             childSize.width +
//             margin.right
//         );
//
//         // totalHeight += s.height;
//         // maxWidth = max(maxWidth, s.width);
//     }
//
//     return {
//         maxWidth,
//         totalHeight
//     };
// }

// auto Column::arrange(const Rect rect) -> void
// {
//     Widget::arrange(rect);
//
//     // -------------------------------------------------
//     // First pass:
//     // calculate total content height
//     // -------------------------------------------------
//
//     int contentHeight = 0;
//
//     bool first = true;
//
//     for (const auto& child : m_children)
//     {
//         const Size childSize =
//             child->measure({
//                 rect.width,
//                 rect.height
//             });
//
//         const auto& margin =
//             child->layout().margin;
//
//         if (!first)
//         {
//             contentHeight += m_props.gap;
//         }
//         else
//         {
//             first = false;
//         }
//
//         contentHeight +=
//             margin.top +
//             childSize.height +
//             margin.bottom;
//     }
//
//     // -------------------------------------------------
//     // Main axis alignment
//     // -------------------------------------------------
//
//     int y = rect.y;
//
//     switch (m_props.mainAxisAlignment)
//     {
//     case MainAxisAlignment::Center:
//         {
//             y +=
//                 (rect.height - contentHeight) / 2;
//             break;
//         }
//
//     case MainAxisAlignment::End:
//         {
//             y +=
//                 rect.height - contentHeight;
//             break;
//         }
//
//     case MainAxisAlignment::Start:
//     default:
//         break;
//     }
//
//     // -------------------------------------------------
//     // Arrange children
//     // -------------------------------------------------
//
//     first = true;
//
//     for (const auto& child : m_children)
//     {
//         const Size childSize =
//             child->measure({
//                 rect.width,
//                 rect.height
//             });
//
//         const auto& margin =
//             child->layout().margin;
//
//         if (!first)
//         {
//             y += m_props.gap;
//         }
//         else
//         {
//             first = false;
//         }
//
//         y += margin.top;
//
//         // ---------------------------------------------
//         // Cross axis alignment
//         // ---------------------------------------------
//
//         int x = rect.x;
//         int width = childSize.width;
//
//         switch (m_props.crossAxisAlignment)
//         {
//         case CrossAxisAlignment::Center:
//             {
//                 x +=
//                     (rect.width - childSize.width) / 2;
//                 break;
//             }
//
//         case CrossAxisAlignment::End:
//             {
//                 x +=
//                     rect.width - childSize.width - margin.right;
//                 break;
//             }
//
//         case CrossAxisAlignment::Stretch:
//             {
//                 width =
//                     rect.width -
//                     margin.left -
//                     margin.right;
//
//                 x += margin.left;
//
//                 break;
//             }
//
//         case CrossAxisAlignment::Start:
//         default:
//             {
//                 x += margin.left;
//                 break;
//             }
//         }
//
//         // ---------------------------------------------
//         // Arrange child
//         // ---------------------------------------------
//
//         child->arrange({
//             x,
//             y,
//             width,
//             childSize.height
//         });
//
//         y += childSize.height;
//         y += margin.bottom;
//     }
//
//     // ---------------------------------------------
//
//
//     // int y = rect.y;
//     // bool first = true;
//     //
//     // for (const auto& child : m_children)
//     // {
//     //     // TODO later caching ?
//     //     Size childSize = child->measure({rect.width, rect.height});
//     //     const auto& margin = child->layout().margin;
//     //
//     //     if (!first)
//     //     {
//     //         y += m_props.gap;
//     //     }
//     //     else
//     //     {
//     //         first = false;
//     //     }
//     //
//     //     y += margin.top;
//     //
//     //     child->arrange({
//     //         rect.x + margin.left,
//     //         y,
//     //         rect.width - margin.left - margin.right,
//     //         childSize.height
//     //     });
//     //
//     //     y += childSize.height;
//     //     y += margin.bottom;
//     // }
// }


} // namespace
