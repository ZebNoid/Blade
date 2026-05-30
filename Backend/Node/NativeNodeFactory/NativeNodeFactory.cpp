#include "NativeNodeFactory.h"

#include "App/AppBackend.h"
#include "Logging/Logger.h"
#include "Components/Native/Button/NativeButton.h"
#include "Components/Native/Label/NativeLabel.h"
#include "Components/RenderSurface/RenderSurface.h"
#include "Components/Surface/ImageSurface/ImageSurface.h"
#include "Components/Surface/LabelSurface/LabelSurface.h"
#include "Components/Tray/NativeTray.h"
#include "Render/WindowSurfaceRuntime/WindowSurfaceRuntime.h"
#include "UI/UI.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

namespace {

template <typename Component>
auto CreateWindowChild(AppBackend& backend, NativeCreateContext& context, const Api::ElementCommand& command, const wchar_t* source) -> std::optional<NativeNode>
{
    auto* parent = backend.nodes().get(command.parent);

    if (!parent)
    {
        LOGF_E(L"[Error] %s no parent", source);
        return std::nullopt;
    }

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOGF_E(L"[Error] %s parent is not NativeWindow", source);
        return std::nullopt;
    }

    auto component = std::make_unique<Component>();

    if (!component->create(parentWindow, command.id, context))
    {
        LOGF_E(L"[Error] %s failed", source);
        return std::nullopt;
    }

    component->applyProps(command.props);
    component->applyEvents(command.events);

    return NativeNode{
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(component),
    };
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
        { Api::WidgetTypes::Label, UI::Label },
        { Api::WidgetTypes::Image, UI::ImageSurface },
        { Api::WidgetTypes::ContextArea, Api::ComponentTypes::Surface },
        { Api::WidgetTypes::Tray, Api::ComponentTypes::Tray },
    });

    m_registry.add(Api::ComponentTypes::Window, [this](const auto& command) { return createWindow(command); });
    m_registry.add(Api::ComponentTypes::Button, [this](const auto& command) { return createButton(command); });
    m_registry.add(UI::Surface, [this](const auto& command) { return createSurface(command); });
    m_registry.add(UI::Label, [this](const auto& command) { return createLabelSurface(command); });
    m_registry.add(UI::ImageSurface, [this](const auto& command) { return createImageSurface(command); });
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
    return CreateWindowChild<NativeButton>(*m_backend, m_context, command, L"createButton");
}

auto NativeNodeFactory::createSurface(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    return CreateWindowChild<RenderSurface>(*m_backend, m_context, command, L"createSurface");
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
    return CreateWindowChild<LabelSurface>(*m_backend, m_context, command, L"createLabelSurface");
}

auto NativeNodeFactory::createImageSurface(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    return CreateWindowChild<ImageSurface>(*m_backend, m_context, command, L"createImageSurface");
}

auto NativeNodeFactory::createNativeLabel(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    return CreateWindowChild<NativeLabel>(*m_backend, m_context, command, L"createNativeLabel");
}

} // namespace
