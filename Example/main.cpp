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
        auto trayId = std::make_shared<Api::Id>(Api::InvalidId);
        auto windowId = std::make_shared<Api::Id>(Api::InvalidId);

        *trayId = Tray(
            Menu(
                MenuItem(L"Show").on({
                    .click = [windowId]() -> void
                    {
                        App::Show(*windowId);
                        LOG(L"Show");
                    }
                }),
                MenuItem(L"Hide").on({
                    .click = [windowId]() -> void
                    {
                        App::Hide(*windowId);
                        LOG(L"Hide");
                    }
                }),
                MenuItem(L"Tray Icon",
                         MenuItem(L"app.png").on({
                             .click = [trayId, windowId]() -> void
                             {
                                 App::SetTrayIcon(*trayId, L"test/app.png");
                                 LOG(L"PNG");
                             }
                         }),
                         MenuItem(L"0ad.png").on({
                             .click = [trayId, windowId]()-> void
                             {
                                 App::SetTrayIcon(*trayId, L"test/0ad.png");
                                 LOG(L"PDF");
                             }
                         })
                ),
                MenuSeparator(),
                MenuItem(L"Exit").set({
                    .shortcut = Api::Shortcut::Ctrl(L'Q')
                }).on({.click = []() -> void { App::Quit(); }})
            ).set({
                .trigger = Api::MenuTrigger::RightClick,
            })
        ).set({
            .title = L"Blade Tray",
            .icon = L"test/app.ico",
            .lifetime = Api::Lifetime::Owner,
        }).on({
            .click = [windowId]() -> void
            {
                App::Show(*windowId);
            },
        }).build(this);

        // Window(
        //     Button(L"Button")
        // ).set({
        //     .title = L"Test",
        //     .size = {800, 600},
        //     .placement = Api::WindowPlacement::Manual({3300, 400}),
        // }).build(this);

        *windowId = Window(
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
                        MenuItem(L"Open").on({.click = []() -> void { LOG(L"Menu Open"); }}),
                        MenuItem(L"Close").on({.click = []() -> void { LOG(L"Menu Delete"); }})
                    ).set({.trigger = Api::MenuTrigger::RightClick})
                ).on({
                    .drop = [](const Api::Text& files) -> void
                    {
                        LOGF_D(L"Drop ContextArea:\n%s", files.c_str());
                    },
                })
            )
        ).set({
            .title = L"Context Menu",
            .size = {800, 600},
            .placement = Api::WindowPlacement::Center({0, 0}, 1),
            .lifetime = Api::Lifetime::Ignore,
        }).on({
            .close = [windowId]() -> bool
            {
                App::Hide(*windowId);
                // App::Quit(); // TODO dev only
                LOGF_D(L"Close Window");
                return false;
            },
            .drop = [](const Api::Text& files) -> void
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
