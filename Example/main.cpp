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
        Tray(
            Menu(
                MenuItem(L"Open").on({.click = [] { LOG(L"Open"); }}),
                MenuItem(L"Export",
                         MenuItem(L"PNG").on({.click = [] { LOG(L"PNG"); }}),
                         MenuItem(L"PDF").on({.click = [] { LOG(L"PDF"); }})
                ),
                MenuSeparator(),
                MenuItem(L"Exit").set({
                    .shortcut = Api::Shortcut::Ctrl(L'Q')
                }).on({.click = [] { App::Quit(); }})
            ).set({
                .trigger = Api::MenuTrigger::LeftRight,
            })
        ).set({
            .title = L"Blade Tray",
            .icon = L"test/app.ico",
            // .lifetime = Api::Lifetime::Ignore,
        }).build(this);

        // Window(
        //     Button(L"Button")
        // ).set({
        //     .title = L"Test",
        //     .size = {800, 600},
        //     .placement = Api::WindowPlacement::Manual({3300, 400}),
        // }).build(this);

        Window(
            ContextArea(
                Button(L"File").on({
                    .drop = [](Api::Text files)
                    {
                        LOGF_D(L"Drop Button:\n%s", files.c_str());
                    }
                }),
                Menu(
                    MenuItem(L"Open").on({.click = [] { LOG(L"Menu Open"); }}),
                    MenuItem(L"Close").on({.click = [] { LOG(L"Menu Delete"); }})
                ).set({.trigger = Api::MenuTrigger::RightClick}),
                Menu(
                    MenuItem(L"Reset").on({.click = [] { LOG(L"Menu Reset"); }}),
                    MenuItem(L"Delete").on({.click = [] { LOG(L"Menu Close"); }})
                ).set({.trigger = Api::MenuTrigger::MiddleClick})
            )
        ).set({
            .title = L"Context Menu",
            .size = {800, 600},
            .placement = Api::WindowPlacement::Center({0, 0}, 1),
        }).on({
            .close = []()
            {
                App::Quit();
                return true;
            },
            .drop = [](Api::Text files)
            {
                LOGF_D(L"Drop Window:\n%s", files.c_str());
            }
        }).build(this);


        Window(
                Column(

                    Button(L"Button  Flex")
                    .set({
                        .layout = {
                            .flex = 3,
                        },
                    })
                    , Row(
                        Button(L"Button Flex")
                        , Row().set({
                            .layout = {
                                .flex = 1,
                            },
                        })
                        , Button(L"Button")
                    )
                    , Button(L"Button Flex Click")
                      .set({
                          .layout = {
                              .flex = 1,
                          },
                          .isDefault = true
                      })
                      .on({
                          .click = []() -> void
                          {
                              LOG(L"Click! 1");
                          },
                      })
                ).set({
                    .gap = 8,
                    .layout = {
                        .padding = 8,
                    },
                    .mainAxisAlignment = MainAxisAlignment::End,
                })
            ).set({
                .title = L"Test",
                // .icon = L"app.ico",
                // .icon = L"app.png",
                .icon = L"test/app.png",
                // .icon = L"test/app.ico",
                .size = {800, 600},
                .minSize = {400, 400},
                // .maxSize = {1000,800},
                // .resizable = false,
                // .placement = Api::WindowPlacement::Default(),
                // .placement = Api::WindowPlacement::Center(),
                // .placement = Api::WindowPlacement::Manual({3500, 200}),
                .placement = Api::WindowPlacement::Center({0, 0}, 1),
                // .placement = Api::WindowPlacement::TopFill(),
                // .placement = Api::WindowPlacement::TopRight({-20, 20},1),
                // .placement = Api::WindowPlacement::LeftFill({}, 1),
                // .placement = Api::WindowPlacement::Fill({}, 1),
                // .state = Api::WindowState::Maximized, // TODO strange behavior with maxSize
                // .state = Api::WindowState::Minimized,
                // .state = Api::WindowState::Normal,
            }).on({
                .close = []()
                {
                    LOG(L"Window 1 Close");
                    // TODO fix application won't close from context menu close
                    return Api::EventResult{};
                },
                .drop = [](Api::Text files)
                {
                    LOGF_D(L"Drop:\n%s", files.c_str());
                }
            })
            // .build(this)
            ;


        // Window(
        //     Column(
        //         Button(L"Button Flex Click")
        //         .set({.layout = {.flex = 1,}})
        //         .on({
        //             .click = []() -> void
        //             {
        //                 LOG(L"Click! 2");
        //             },
        //             .focus = [](auto focus)
        //             {
        //                 LOGF(L"Focus! 2 %d", focus);
        //             },
        //         })
        //         , Button(L"Button")
        //     )
        // ).set({
        //     .title = L"Test",
        //     .size = {400, 400},
        //     // .placement = Api::WindowPlacement::Manual({3500, 200}),
        //     .placement = Api::WindowPlacement::TopRight({-20, 20},1),
        // }).build(this);


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
        //     .placement = Api::WindowPlacement::Manual({3300, 400}),
        // }).build(this);


        // Window().set({
        //     .title = L"Test 2",
        //     .size = {400, 500},
        //     .placement = Api::WindowPlacement::Manual({3400, 300}),
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
