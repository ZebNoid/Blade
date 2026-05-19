#include <iostream>

#include "blade.h"
#include "App/AppBackend.h"

using namespace Blade;


class Sandbox : public App
{

protected:
    auto setup() -> void override
    {
        use<Backend::AppBackend>();
    }

    auto ui() -> void override
    {
        // Window().set(wProp).mount(this);

        // Window(Button("Button")).set(wProp).mount(this);
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
