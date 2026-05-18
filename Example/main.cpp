#include <iostream>

#include "blade.h"
#include "WinBackend/WinBackend.h"

using namespace Blade;


class Sandbox : public App
{

    WindowProps wProp = {
        .title = "Blade",
        .position = {3200, 600},
    };

protected:
    auto setup() -> void override
    {
        use<Backend::WinBackend>();
    }

    auto ui() -> void override
    {
        Window().mount(this);

        Window(
                Row(
                    Stack(
                        Nop("Nop")
                        , Nop("Nop")
                        , Nop("Nop").set({.layout = {100, 10,}})
                    )
                    , Stack(
                        Label("Label")
                        , Label("|-----+-----|")
                    )
                )
            )
            .set(wProp)
            .mount(this);


        // window(contentFlex()).set(wProp);
        // window(Label("132")).set(wProp);
    }


    auto contentBladeDemo() -> auto
    {
        return Column(
                Label("Blade Example").id(labelId),
                TextField("Default text")
                .set({
                    .layout = layoutMarginH,
                    .textAlign = TextAlign::Start,
                })
                .on({
                    .change = [](const std::string& value)
                    {
                        std::cout << value << "\n";
                    },
                }),
                Label("Radio Buttons").set(labelStyle),
                Row(
                    RadioButton("RadioButton"),
                    RadioButton("RadioButton").set({
                        .layout = {.flex = 1}
                    }),
                    RadioButton("RadioButton")
                ).set({
                    .gap = gap,
                    .layout = layoutMarginH,
                }),
                Label("Row Buttons").set(labelStyle),
                Row(
                    Button("Default Button").set({
                        .defaultButton = true,
                    }),
                    Button("Button"),
                    Button("Button")
                ).set({
                    .gap = gap,
                    .layout = layoutMarginH,
                    .mainAxisAlignment = MainAxisAlignment::Center,
                    .crossAxisAlignment = CrossAxisAlignment::Stretch,
                }),
                Label("Checkboxes"),
                Row(
                    Checkbox("Checkbox"),
                    Checkbox("Checkbox"),
                    Checkbox("Checkbox")
                ).set({
                    .layout = layoutMarginH,
                    .mainAxisAlignment = MainAxisAlignment::Center,
                    .crossAxisAlignment = CrossAxisAlignment::Center,
                }),
                Button("Button"),
                Progress(100),
                Button("Button"),
                Slider(50),
                Button("Button"),
                Label("Flex").set({.layout = {.flex = 1}}),
                Row(
                    Button("Debug").on({
                        .click = []
                        {
                        },
                    }),
                    Progress(100).set({.marquee = true, .layout = {.flex = 1}}),
                    Label("Footer")
                )
            )
            .set({
                .gap = gap,
                .mainAxisAlignment = MainAxisAlignment::Start,
                .crossAxisAlignment = CrossAxisAlignment::Stretch,
            });
    }

    auto contentFlex() -> auto
    {
        return Column(
            Label("Header"),

            Label("Content").set({
                .layout = {
                    .flex = 1
                }
            }),

            Label("Footer")
        ).set({
            .mainAxisAlignment = MainAxisAlignment::Center,
            .crossAxisAlignment = CrossAxisAlignment::Stretch,
        });
    }

public:
    const int gap = 8;

    const LayoutProps layoutMarginH = {
        .margin = {gap, 0}
    };

    const LabelProps labelStyle = {
        .layout = {
            .margin = {gap, 0},
        },
        .textAlign = TextAlign::Start,
    };

    WidgetId windowId;
    WidgetId textFieldId;
    WidgetId labelId;
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
