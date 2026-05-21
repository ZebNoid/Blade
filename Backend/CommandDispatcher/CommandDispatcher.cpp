#include "CommandDispatcher.h"

#include "App/AppBackend.h"
#include "Node/NativeNode/NativeNode.h"
#include "Property/PropertyMapUtils/PropertyMapUtils.h"


namespace Blade::Backend {

CommandDispatcher::CommandDispatcher(AppBackend* backend) : m_backend(backend)
{
}

auto CommandDispatcher::dispatch(
    const Api::BackendCommand& command
) -> void
{
    std::wcout << "BackendCommand::" << to_string(command.command) << " -> " << command.nodeType << "\n";

    switch (command.command)
    {
    case Api::CommandType::Create:
        create(command);
        break;

    case Api::CommandType::Attach:
        attach(command);
        break;

    case Api::CommandType::Remove:
        remove(command);
        break;

    default:
        break;
    }
}

auto CommandDispatcher::create(const Api::BackendCommand& command) -> void
{
    if (command.nodeType == L"Window")
    {
        auto* nativeWindow = m_backend->windows().createWindow();

        applyWindowProps(
           nativeWindow,
           command.props
        );

        nativeWindow->router().on(
            WM_CLOSE,
            [](HWND hwnd, UINT, WPARAM, LPARAM)
            {
                DestroyWindow(hwnd);
                return 0;
            }
        );

        nativeWindow->router().on(
            WM_DESTROY,
            [nativeWindow](HWND, UINT, WPARAM, LPARAM)
            {
                nativeWindow->markDead();
                return 0;
            }
        );

        NativeNode node = {
            .id = command.id,
            .type = command.nodeType,
            .hwnd = nativeWindow->handle(),
            .parent = command.parent,
        };

        m_backend->nodes().add(
            std::move(node)
        );

        return;
    }

    if (command.nodeType == L"Button")
    {
        // TODO
        return;
    }
}

auto CommandDispatcher::attach(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::remove(const Api::BackendCommand& command) -> void
{
}

auto CommandDispatcher::applyWindowProps(
    NativeWindow* window,
    const Api::PropertyMap& props
) -> void
{
    if (const auto* title =
        PropertyMapUtils::get<Api::Text>(
            props,
            Api::Props::Title
        ))
    {
        SetWindowTextW(
            window->handle(),
            title->c_str()
        );
    }

    if (const auto* size =
        PropertyMapUtils::get<Api::Size>(
            props,
            Api::Props::Size
        ))
    {
        SetWindowPos(
            window->handle(),
            nullptr,
            0,
            0,
            size->width,
            size->height,
            SWP_NOMOVE | SWP_NOZORDER
        );
    }
}


} // namespace
