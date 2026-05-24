#include <iostream>

#include "blade.h"
#include "App/AppBackend.h"
#include "Common/Logger.h"

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
                Button(L"Button 1")
                .set({
                    .isDefault = true,
                })
                .set({
                    .layout = {
                        .flex = 1,
                    },
                    .isDefault = false
                })
                .on({
                    .click = []() -> void
                    {
                        LOG(L"Click! 1");
                    },
                })
                , Button(L"Button")
            ).set({
                .mainAxisAlignment = MainAxisAlignment::End,
            })
        ).set({
            .title = L"Test",
            .size = {800, 600},
            .position = {3300, 400},
        }).build(this);


        Window(
            Column(
                Button(L"Button 2")
                .set({.layout = {.flex = 1,}})
                .on({
                    .click = []() -> void
                    {
                        LOG(L"Click! 2");
                    },
                })
                , Button(L"Button")
            )
        ).set({
            .title = L"Test",
            .size = {400, 400},
            .position = {3500, 200},
        }).build(this);


        // Window(
        //     Column(
        //         Row(
        //             Button(L"One"),
        //             Button(L"Two").set({.layout = {.flex = 1,},})
        //         )
        //         // .set({.gap = 8, .mainAxisAlignment = MainAxisAlignment::End})
        //         , Button(L"Button")
        //         , Button(L"Button2")//.set({.layout = {.flex = 1,},})
        //         // , Stack(
        //         //     Button(L"Back"),
        //         //     Button(L"Front")
        //         // )
        //     ).set({
        //         .gap = 12,
        //         .layout = {.flex = 1,},
        //         .mainAxisAlignment = MainAxisAlignment::End,
        //         .crossAxisAlignment = CrossAxisAlignment::Stretch,
        //     })
        // ).set({
        //     .title = L"Test",
        //     .size = {800, 600},
        //     .position = {3300, 400},
        // }).build(this);


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
