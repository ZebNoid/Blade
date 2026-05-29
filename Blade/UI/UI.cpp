#include "UI.h"

#include "App/App.h"

namespace Blade {

auto UI::Show(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::Show, .target = id });
}

auto UI::Hide(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::Hide, .target = id });
}

auto UI::Unmount(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::UnmountRoot, .target = id });
}

auto UI::Window::Close(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::WindowClose, .target = id });
}

auto UI::Window::Minimize(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::WindowMinimize, .target = id });
}

auto UI::Window::Maximize(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::WindowMaximize, .target = id });
}

auto UI::Window::Restore(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::WindowRestore, .target = id });
}

auto UI::Tray::Icon(Api::Id id, Api::Text icon) -> void
{
    Send({ .command = Api::AppCommandType::TrayIcon, .target = id, .payload = std::move(icon) });
}

auto UI::Tray::Title(Api::Id id, Api::Text title) -> void
{
    Send({ .command = Api::AppCommandType::TrayTitle, .target = id, .payload = std::move(title) });
}

auto UI::Send(Api::AppCommand command) -> void
{
    App::Process(std::move(command));
}

} // namespace Blade
