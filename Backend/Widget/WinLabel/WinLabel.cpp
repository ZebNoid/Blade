#include "WinLabel.h"

#include "Registry/ClassRegistry/ClassRegistry.h"


namespace Blade::Backend {


auto WinLabel::create(
    const WidgetContext& ctx,
    WidgetId id,
    const LabelProps& props,
    const std::string& text
) -> void
{
    WinCustom::create(ctx, id);
    m_props = props;
    m_text = Utf8ToUtf16(text);

    // ClassRegistry::Register(
    //     "BladeLabel",
    //     {
    //         .name = L"BladeLabel",
    //         .proc = WindowProc,
    //         .background = nullptr
    //     }
    // );

    // TODO size are ignoring and recalculated in
    createNative(Rect{});
}

auto WinLabel::paint(HDC hdc, RECT rect) -> void
{
    auto style = DT_VCENTER |
        DT_SINGLELINE |
        DT_END_ELLIPSIS;

    switch (m_props.textAlign)
    {
    case TextAlign::Start:
        style |= DT_LEFT;
        break;
    case TextAlign::End:
        style |= DT_RIGHT;
        break;
    default:
        style |= DT_CENTER;
    }

    m_render.text(
        hdc,
        rect,
        m_text,
        RGB(0, 0, 0),
        m_systemFont,
        style
    );
}


} // namespace
