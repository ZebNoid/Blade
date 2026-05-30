#include "NativeNodeFactory.h"

#include <memory>
#include <windowsx.h>

#include "App/AppBackend.h"
#include "Logging/Logger.h"
#include "Components/Custom/Surface/NativeCustom.h"
#include "Components/Native/Button/NativeButton.h"
#include "Components/Native/Label/NativeLabel.h"
#include "Components/Tray/NativeTray.h"
#include "UI/UI.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"


namespace Blade::Backend {

namespace {

auto PointFromLParam(LPARAM lParam) -> Api::Point
{
    return {
        .x = GET_X_LPARAM(lParam),
        .y = GET_Y_LPARAM(lParam)
    };
}

auto ToClientPoint(HWND hwnd, POINT point) -> Api::Point
{
    ScreenToClient(hwnd, &point);
    return {point.x, point.y};
}

} // namespace

NativeNodeFactory::NativeNodeFactory(AppBackend* backend)
    : m_backend(backend)
    , m_context{
          .instance = backend->handle(),
          .resources = &backend->resources(),
          .renderNodes = &backend->renderNodes(),
      }
{
    registerFactories();
}

auto NativeNodeFactory::create(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    const auto component = m_bindings.resolve(command.nodeType);
    return m_registry.create(component, command);
}

auto NativeNodeFactory::bind(Api::WidgetType widget, Api::ComponentType component) -> void
{
    m_bindings.bind(widget, component);
}

auto NativeNodeFactory::bind(const NativeBindings& bindings) -> void
{
    m_bindings.bind(bindings);
}

auto NativeNodeFactory::defaultBindings() const -> std::vector<NativeBindingInfo>
{
    return m_bindings.defaultBindings();
}

auto NativeNodeFactory::supportedComponents() const -> std::vector<ComponentInfo>
{
    return m_bindings.supportedComponents();
}

auto NativeNodeFactory::registerFactories() -> void
{
    m_bindings.bind({
        { Api::WidgetTypes::Window, Api::ComponentTypes::Window },
        { Api::WidgetTypes::Button, Api::ComponentTypes::Button },
        { Api::WidgetTypes::Label, Api::ComponentTypes::Label },
        { Api::WidgetTypes::ContextArea, Api::ComponentTypes::Surface },
        { Api::WidgetTypes::Tray, Api::ComponentTypes::Tray },
    });

    m_registry.add(Api::ComponentTypes::Window, [this](const auto& command) { return createWindow(command); });
    m_registry.add(Api::ComponentTypes::Button, [this](const auto& command) { return createButton(command); });
    m_registry.add(UI::Surface, [this](const auto& command) { return createSurface(command); });
    m_registry.add(Api::ComponentTypes::Label, [this](const auto& command) { return createLabel(command); });
    m_registry.add(Api::ComponentTypes::Tray, [this](const auto& command) { return createTray(command); });
}

auto NativeNodeFactory::createWindow(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto nativeWindow = std::make_unique<NativeWindow>();

    if (!nativeWindow)
    {
        return std::nullopt;
    }

    nativeWindow->create(m_backend->handle(), command.id);
    nativeWindow->commandRouter().setHandler(m_backend->messageHandler());

    nativeWindow->router().on(
        WM_SIZE,
        [this, windowId = command.id](HWND hwnd, UINT, WPARAM wParam, LPARAM lParam) -> int
        {
            if (wParam == SIZE_MINIMIZED)
            {
                return 0;
            }

            HwndApi::Invalidate(hwnd);
            m_backend->onWindowResize(windowId, HwndApi::GetSizeFromLParam(lParam));
            return 0;
        }
    );

    nativeWindow->router().on(
        WM_GETMINMAXINFO,
        [window = nativeWindow.get()](HWND, UINT, WPARAM, LPARAM lParam) -> int
        {
            window->applyMinMax(reinterpret_cast<MINMAXINFO*>(lParam));
            return 0;
        }
    );

    nativeWindow->router().on(
        WM_PAINT,
        [this](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            PAINTSTRUCT paint{};
            const auto hdc = BeginPaint(hwnd, &paint);
            RenderApi::Fill(hdc, HwndApi::GetClientRect(hwnd), m_backend->resources().windowBrush());

            m_backend->nodes().forEach(
                [this, hdc](NativeNode& node)
                {
                    auto* label = dynamic_cast<NativeLabel*>(node.native.get());
                    if (label) label->paint(hdc, m_backend->resources(), m_backend->renderNodes());
                }
            );

            EndPaint(hwnd, &paint);
            return 0;
        }
    );

    auto pressedLabel = std::make_shared<Api::Id>(Api::InvalidId);
    auto focusedLabel = std::make_shared<Api::Id>(Api::InvalidId);

    auto hitLabel = [this](Api::Point point, bool requireDrop = false) -> NativeLabel*
    {
        NativeLabel* result = nullptr;
        int resultOrder = -1;

        m_backend->nodes().forEach(
            [&](NativeNode& node)
            {
                auto* label = dynamic_cast<NativeLabel*>(node.native.get());
                if (!label || !label->hitTest(point)) return;
                if (requireDrop && !label->wantsDrop()) return;

                const auto* render = m_backend->renderNodes().get(node.id);
                const auto order = render ? render->order : 0;
                if (!result || order >= resultOrder)
                {
                    result = label;
                    resultOrder = order;
                }
            }
        );

        return result;
    };

    auto labelById = [this](Api::Id id) -> NativeLabel*
    {
        const auto* node = m_backend->nodes().get(id);
        return node ? dynamic_cast<NativeLabel*>(node->native.get()) : nullptr;
    };

    nativeWindow->setDropTargetResolver(
        [window = nativeWindow.get(), hitLabel](POINT screenPoint) -> Api::Id
        {
            auto* label = hitLabel(ToClientPoint(window->handle(), screenPoint), true);
            return label ? label->id() : Api::InvalidId;
        }
    );

    nativeWindow->router().on(
        WM_LBUTTONDOWN,
        [this, hitLabel, labelById, pressedLabel, focusedLabel](HWND hwnd, UINT, WPARAM, LPARAM lParam) -> int
        {
            auto* label = hitLabel(PointFromLParam(lParam));
            if (!label) return 1;

            if (*focusedLabel != label->id())
            {
                if (auto* previous = labelById(*focusedLabel); previous && previous->focus(m_backend->renderNodes(), false)) HwndApi::Invalidate(hwnd);
                *focusedLabel = label->id();
                if (label->focus(m_backend->renderNodes(), true)) HwndApi::Invalidate(hwnd);
            }

            *pressedLabel = label->id();
            SetCapture(hwnd);
            if (label->mouseDown(m_backend->renderNodes())) HwndApi::Invalidate(hwnd);
            return 0;
        }
    );

    nativeWindow->router().on(
        WM_LBUTTONUP,
        [this, labelById, pressedLabel](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            if (*pressedLabel == Api::InvalidId) return 1;

            if (GetCapture() == hwnd) ReleaseCapture();
            if (auto* label = labelById(*pressedLabel); label && label->mouseUp(m_backend->renderNodes())) HwndApi::Invalidate(hwnd);
            *pressedLabel = Api::InvalidId;
            return 0;
        }
    );

    m_backend->host().attach(nativeWindow.get());

    nativeWindow->applyProps(command.props);
    nativeWindow->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(nativeWindow),
    };

    return node;
}

auto NativeNodeFactory::createButton(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        LOG_E(L"[Error] createButton no parent");
        return std::nullopt;
    }

    auto button = std::make_unique<NativeButton>();

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOG_E(L"[Error] createButton parent is not NativeWindow");
        return std::nullopt;
    }

    if (!button->create(parentWindow, command.id, m_context))
    {
        LOG_E(L"[Error] createButton failed");
        return std::nullopt;
    }

    button->applyProps(command.props);
    button->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(button),
    };

    return node;
}

auto NativeNodeFactory::createSurface(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        LOG_E(L"[Error] createSurface no parent");
        return std::nullopt;
    }

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOG_E(L"[Error] createSurface parent is not NativeWindow");
        return std::nullopt;
    }

    auto surface = std::make_unique<NativeCustom>();

    if (!surface->create(parentWindow, command.id, m_context))
    {
        LOG_E(L"[Error] createSurface failed");
        return std::nullopt;
    }

    surface->applyProps(command.props);
    surface->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(surface),
    };

    return node;
}

auto NativeNodeFactory::createTray(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto tray = std::make_unique<NativeTray>();

    if (!tray->create(m_backend->handle(), command.id, m_backend->messageHandler()))
    {
        LOG_E(L"[Error] createTray failed");
        return std::nullopt;
    }

    tray->applyProps(command.props);
    tray->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(tray),
    };

    return node;
}

auto NativeNodeFactory::createLabel(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        LOG_E(L"[Error] createLabel no parent");
        return std::nullopt;
    }

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOG_E(L"[Error] createLabel parent is not NativeWindow");
        return std::nullopt;
    }

    auto label = std::make_unique<NativeLabel>();

    if (!label->create(parentWindow, command.id, m_context))
    {
        LOG_E(L"[Error] createLabel failed");
        return std::nullopt;
    }

    label->applyProps(command.props);
    label->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(label),
    };

    return node;
}

} // namespace
