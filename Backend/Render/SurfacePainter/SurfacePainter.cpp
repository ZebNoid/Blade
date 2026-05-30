#include "SurfacePainter.h"

#include <algorithm>
#include <vector>

#include "App/AppBackend.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

struct PaintItem
{
    int order = 0;
    Api::Id id = Api::InvalidId;
    RenderSurface* surface = nullptr;
};

auto PaintVirtuals(AppBackend& backend, HDC hdc) -> void
{
    std::vector<PaintItem> items;

    backend.nodes().forEach(
        [&items](NativeNode& node)
        {
            if (auto* surface = dynamic_cast<RenderSurface*>(node.native.get())) items.push_back({node.order, node.id, surface});
        }
    );

    std::ranges::sort(
        items,
        [](const auto& left, const auto& right)
        {
            if (left.order != right.order) return left.order < right.order;
            return left.id < right.id;
        }
    );

    for (const auto& item : items)
    {
        item.surface->paint(hdc, backend.resources(), backend.renderNodes());
    }
}

} // namespace

namespace Surface::Painter {

auto PaintBuffered(HWND hwnd, HDC target, AppBackend& backend) -> void
{
    const auto rect = HwndApi::GetClientRect(hwnd);
    if (rect.width <= 0 || rect.height <= 0) return;

    auto memoryDc = CreateCompatibleDC(target);
    auto bitmap = CreateCompatibleBitmap(target, rect.width, rect.height);
    auto oldBitmap = SelectObject(memoryDc, bitmap);

    RenderApi::Fill(memoryDc, rect, backend.resources().windowBrush());
    PaintVirtuals(backend, memoryDc);
    BitBlt(target, 0, 0, rect.width, rect.height, memoryDc, 0, 0, SRCCOPY);

    SelectObject(memoryDc, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(memoryDc);
}

} // namespace Surface::Painter

} // namespace Blade::Backend
