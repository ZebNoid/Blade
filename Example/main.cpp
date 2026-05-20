#include <iostream>

#include "blade.h"
#include "App/AppBackend.h"

using namespace Blade;


class Sandbox : public App
{
protected:
    auto setup() -> void override
    {
        use(Backend::AppBackend{});
    }

    auto ui() -> Api::WidgetTree override
    {
        return Window(
            Button(L"Button").set({.id = 1,})
        ).buildTree();
        // return Window().buildTree();
        // return Button(L"Button").buildTree();

        // Window(Nop()).mount(this);
        // Window().set(wProp).mount(this);
        // Window(Button("Button")).set(wProp).mount(this);
    }
};


auto main() -> int
{
    Sandbox app;
    return app.run();
}
