#include "NativeNodeFactory.h"

#include "App/AppBackend.h"
#include "Common/Logger.h"
#include "Components/Button/NativeButton.h"
#include "Components/ContextArea/NativeContextArea.h"
#include "Components/Label/NativeLabel/NativeLabel.h"
#include "Components/Tray/NativeTray.h"
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
    return m_registry.create(command);
}

auto NativeNodeFactory::registerFactories() -> void
{
    m_registry.add(Api::WidgetTypes::Window, [this](const auto& command) { return createWindow(command); });
    m_registry.add(Api::WidgetTypes::Button, [this](const auto& command) { return createButton(command); });
    m_registry.add(Api::WidgetTypes::ContextArea, [this](const auto& command) { return createContextArea(command); });
    m_registry.add(Api::WidgetTypes::Label, [this](const auto& command) { return createLabel(command); });
    m_registry.add(Api::WidgetTypes::Tray, [this](const auto& command) { return createTray(command); });
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

auto NativeNodeFactory::createContextArea(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    auto* parent = m_backend->nodes().get(command.parent);

    if (!parent)
    {
        LOG_E(L"[Error] createContextArea no parent");
        return std::nullopt;
    }

    auto* parentWindow = dynamic_cast<NativeWindow*>(parent->native.get());

    if (!parentWindow)
    {
        LOG_E(L"[Error] createContextArea parent is not NativeWindow");
        return std::nullopt;
    }

    auto area = std::make_unique<NativeContextArea>();

    if (!area->create(parentWindow, command.id, m_context))
    {
        LOG_E(L"[Error] createContextArea failed");
        return std::nullopt;
    }

    area->applyProps(command.props);
    area->applyEvents(command.events);

    NativeNode node = {
        .id = command.id,
        .type = command.nodeType,
        .parent = command.parent,
        .native = std::move(area),
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
