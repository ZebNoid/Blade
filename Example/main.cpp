#include <iostream>

#include "blade.h"
#include "App/AppBackend.h"

using namespace Blade;


class Sandbox : public App
{

    // WindowProps wProp = {
    //     .title = L"Blade Example",
    //     .size = {600,200},
    //     .position = {3200, 600},
    // };

protected:
    auto setup() -> void override
    {
        use<Backend::AppBackend>();
    }

    auto ui() -> void override
    {
        // Window().set(wProp).mount(this);

        // Window(Button("Button")).set(wProp).mount(this);


        // Window(Nop("Nop")).set(wProp).mount(this);
        // Window(Label("Label")).set(wProp).mount(this);
        // Window(Column(Nop(), Nop())).set(wProp).mount(this);
        // Window(Column(Label("Label"), Label("Label"))).set(wProp).mount(this);
        // Window(Column(Button("1"), Button("2"))).set(wProp).mount(this);
        // Window(Column(Button("1"))).set(wProp).mount(this);

        // Window(Column(Nop(), Label("Label"))).set(wProp).mount(this);
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
