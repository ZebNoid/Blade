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

    auto testButton() -> auto
    {
        return Button(L"testButton");
    }

    auto testWindow() -> auto
    {
        return Window(
                Column(
                    Button(L"Button"),
                    testButton().flex(1)
                )
            ).title(L"Test")
             .size({800, 600})
             .placement(Api::WindowPlacement::BottomRight({-50, -50}, 1));
    }


    auto onCreate() -> void override
    {
        auto trayId = std::make_shared<Api::Id>(Api::InvalidId);
        auto windowId = std::make_shared<Api::Id>(Api::InvalidId);

        // testWindow().mount();

        *trayId = Tray(
                Menu(
                    MenuItem(L"Show").onClick([windowId]() -> void
                    {
                        UI::Show(*windowId);
                        LOG(L"Show");
                    }),
                    MenuItem(L"Hide").onClick([windowId]() -> void
                    {
                        UI::Hide(*windowId);
                        LOG(L"Hide");
                    }),
                    MenuItem(L"Tray Icon",
                             MenuItem(L"app.png").onClick([trayId, windowId]() -> void
                             {
                                 UI::Tray::Icon(*trayId, L"test/app.png");
                                 LOG(L"PNG");
                             }),
                             MenuItem(L"0ad.png").onClick([trayId, windowId]()-> void
                             {
                                 UI::Tray::Icon(*trayId, L"test/0ad.png");
                                 LOG(L"PDF");
                             })
                    ),
                    MenuSeparator(),
                    MenuItem(L"Exit")
                    .shortcut(Api::Shortcut::Ctrl(L'Q'))
                    .onClick([]() -> void { App::Quit(); })
                ).trigger(Api::MenuTrigger::RightClick)
            ).title(L"Blade Tray")
             .icon(L"test/app.ico")
             .lifetime(Api::Lifetime::Owner)
             .onClick([windowId]() -> void
             {
                 UI::Show(*windowId);
             })
             .mount();

        // Window(
        //     Button(L"Button")
        // ).title(L"Test")
        //  .size({800, 600})
        //  .placement(Api::WindowPlacement::Manual({3300, 400}))
        //  .mount();

        *windowId = Window(
                Column(
                    Button(L"Flex")
                    , Stack(
                        Button(L"Flex")
                        , Button(L"Flex").padding(8)
                        , Label(L"------------ Native Label ------------------------------------")
                          .padding(16)
                          .borderRadius(8)
                          .states({
                              .normal = Api::Modifier().background(Api::Color::Green()),
                              .hover = Api::Modifier().background(Api::Color::Red()),
                              .focus = Api::Modifier().background(Api::Color::Blue()),
                              .pressed = Api::Modifier().background(Api::Color::DarkRed()),
                              .disabled = Api::Modifier().background(Api::Color::Gray()),
                          })
                          .borderColor(Api::Color::Black())
                          .padding(16)
                          .color(Api::Color::White())
                        , Label(L" | | | | | | Native Label").padding(12)
                    )
                    , Button(L"Button").padding(8)
                    , Label(L"------------ Label States ------------------------------------")
                      .padding(16)
                      .size({40, 40})
                      .borderRadius(8)
                      .states({
                          .normal = Api::Modifier().background(Api::Color::Green()),
                          .hover = Api::Modifier().background(Api::Color::Red()),
                          .focus = Api::Modifier().background(Api::Color::Blue()),
                          .pressed = Api::Modifier().background(Api::Color::DarkRed()),
                          .disabled = Api::Modifier().background(Api::Color::Gray()),
                      })
                      .borderColor(Api::Color::Black())
                      .padding(16)
                      .color(Api::Color::White())
                    , Label(L" | | | | | | Native Label").padding(12)
                    , ContextArea(
                        Column(
                            Label(L"------------ Label States 2 ------------------------------------")
                            .flex(1)
                            .padding(16)
                            .size({40, 40})
                            .borderRadius(8)
                            .states({
                                .normal = Api::Modifier().background(Api::Color::Green()),
                                .hover = Api::Modifier().background(Api::Color::Red()),
                                .focus = Api::Modifier().background(Api::Color::Blue()),
                                .pressed = Api::Modifier().background(Api::Color::DarkRed()),
                                .disabled = Api::Modifier().background(Api::Color::Gray()),
                            })
                        ).flex(1)
                        // Button(L"File").onDrop([](Api::Text files) { LOGF_D(L"Drop Button:\n%s", files.c_str()); })
                        , Menu(
                            MenuItem(L"Open").onClick([]() -> void { LOG(L"Menu Open"); }),
                            MenuItem(L"Close").onClick([]() -> void { LOG(L"Menu Delete"); })
                        ).trigger(Api::MenuTrigger::RightClick)
                    ).onDrop([](const Api::Text& files) -> void
                    {
                        LOGF_D(L"Drop ContextArea:\n%s", files.c_str());
                    })
                )
            ).title(L"Context Menu")
             .size({800, 600})
             .placement(Api::WindowPlacement::Center({0, 0}, 1))
             .lifetime(Api::Lifetime::Ignore)
             .onClose([windowId]() -> bool
             {
                 UI::Hide(*windowId);
                 App::Quit(); // TODO dev only
                 LOGF_D(L"Close Window");
                 return false;
             })
             .onDrop([](const Api::Text& files) -> void
             {
                 LOGF_D(L"Drop Window:\n%s", files.c_str());
             })
             .mount();
    }
};


auto main() -> int
{
    Sandbox app;
    return app.run();
}
