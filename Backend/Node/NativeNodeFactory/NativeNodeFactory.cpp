#include "NativeNodeFactory.h"

#include "App/AppBackend.h"
#include "Logging/Logger.h"
#include "Components/Native/Button/NativeButton.h"
#include "Components/Native/Label/NativeLabel.h"
#include "Components/RenderSurface/LabelSurface/LabelSurface.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Components/Tray/NativeTray.h"
#include "Render/WindowSurfaceRuntime/WindowSurfaceRuntime.h"
#include "UI/UI.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

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
        { Api::WidgetTypes::Label, UI::Label },
        { Api::WidgetTypes::ContextArea, Api::ComponentTypes::Surface },
        { Api::WidgetTypes::Tray, Api::ComponentTypes::Tray },
    });

    m_registry.add(Api::ComponentTypes::Window, [this](const auto& command) { return createWindow(command); });
    m_registry.add(Api::ComponentTypes::Button, [this](const auto& command) { return createButton(command); });
    m_registry.add(UI::Surface, [this](const auto& command) { return createSurface(command); });
    m_registry.add(UI::Label, [this](const auto& command) { return createLabelSurface(command); });
    m_registry.add(UI::LabelNative, [this](const auto& command) { return createNativeLabel(command); });
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

    WindowSurfaceRuntime::Attach(*m_backend, *nativeWindow);

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

    auto surface = std::make_unique<RenderSurface>();

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

auto NativeNodeFactory::createLabelSurface(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        LOG_E(L"[Error] createLabelSurface no parent");
        return std::nullopt;
    }

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOG_E(L"[Error] createLabelSurface parent is not NativeWindow");
        return std::nullopt;
    }

    auto label = std::make_unique<LabelSurface>();

    if (!label->create(parentWindow, command.id, m_context))
    {
        LOG_E(L"[Error] createLabelSurface failed");
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

auto NativeNodeFactory::createNativeLabel(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        LOG_E(L"[Error] createNativeLabel no parent");
        return std::nullopt;
    }

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOG_E(L"[Error] createNativeLabel parent is not NativeWindow");
        return std::nullopt;
    }

    auto label = std::make_unique<NativeLabel>();

    if (!label->create(parentWindow, command.id, m_context))
    {
        LOG_E(L"[Error] createNativeLabel failed");
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
