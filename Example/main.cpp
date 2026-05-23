#include <iostream>

#include "blade.h"
#include "App/AppBackend.h"

using namespace Blade;


class Sandbox : public App
{
protected:
    auto onSetup() -> void override
    {
        // use(Backend::AppBackend{});
        use<Backend::AppBackend>();
    }

    auto onCreate() -> void override
    {
        // Window(
        //     Button(L"Button")
        // ).set({
        //     .title = L"Test",
        //     .size = {800, 600},
        //     .position = {3300, 400},
        // }).build(this);

        Window(
            Column(
                Button(L"Button"),
                Button(L"Button").set({.isDefault = true,})
            )
        ).set({
            .title = L"Test",
            .size = {800, 600},
            .position = {3300, 400},
        }).build(this);


        // Window().set({
        //     .title = L"Test 2",
        //     .size = {400, 500},
        //     .position = {3400, 300},
        // }).build(this);

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
