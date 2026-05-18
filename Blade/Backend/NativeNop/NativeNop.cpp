#include "NativeNop.h"

#include "Backend/NativeRender/NativeRender.h"


namespace Blade {


auto NativeNop::create(const WidgetContext& ctx, WidgetId id, const NopProps& props, const std::string& text) -> void
{
    NativeCustom::create(ctx, id);
    m_props = props;
    m_text = text;
}

auto NativeNop::paint(HDC hdc) -> void
{
    NativeRenderContext ctx{
        .hdc = hdc
    };

    Backend::NativeRender::FillRect(
        ctx,
        rect(),
        {40, 40, 40}
    );

    Backend::NativeRender::DrawRect(
        ctx,
        rect(),
        {255, 0, 0},
        2
    );

    Backend::NativeRender::DrawLine(
        ctx,
        rect().x,
        rect().y,
        rect().x + rect().width,
        rect().y + rect().height,
        {255, 0, 0}
    );

    Backend::NativeRender::DrawLine(
        ctx,
        rect().x + rect().width,
        rect().y,
        rect().x,
        rect().y + rect().height,
        {255, 0, 0}
    );

    Backend::NativeRender::DrawText(
        ctx,
        rect(),
        m_text,
        {255, 255, 255}
    );
}
} // namespace
