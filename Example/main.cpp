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
            Column(
                Button(L"Flex") //.set({.layout = {.flex = 1,},})
                , ContextArea(
                    Column().set({.layout = {.flex = 1,},})
                    // Button(L"File") //.set({.layout = {.flex = 1,},})
                    // .on({
                    //     .drop = [](Api::Text files)
                    //     {
                    //         LOGF_D(L"Drop Button:\n%s", files.c_str());
                    //     }
                    // })
                    , Menu(
                        MenuItem(L"Open").on({.click = [] { LOG(L"Menu Open"); }}),
                        MenuItem(L"Close").on({.click = [] { LOG(L"Menu Delete"); }})
                    ).set({.trigger = Api::MenuTrigger::RightClick})
                ).on({
                .drop = [](Api::Text files)
                {
                    LOGF_D(L"Drop ContextArea:\n%s", files.c_str());
                },
                })
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
    }
};


auto main() -> int
{
    Sandbox app;
    return app.run();
}
