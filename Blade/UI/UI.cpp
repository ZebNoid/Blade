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

auto UI::Window::Close(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::CloseWindow, .target = id });
}

auto UI::Window::Minimize(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::MinimizeWindow, .target = id });
}

auto UI::Window::Maximize(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::MaximizeWindow, .target = id });
}

auto UI::Window::Restore(Api::Id id) -> void
{
    Send({ .command = Api::AppCommandType::RestoreWindow, .target = id });
}

auto UI::Tray::Icon(Api::Id id, Api::Text icon) -> void
{
    Send({ .command = Api::AppCommandType::SetTrayIcon, .target = id, .payload = std::move(icon) });
}

auto UI::Tray::Title(Api::Id id, Api::Text title) -> void
{
    Send({ .command = Api::AppCommandType::SetTrayTitle, .target = id, .payload = std::move(title) });
}

auto UI::Send(Api::AppCommand command) -> void
{
    App::Process(std::move(command));
}

} // namespace Blade
