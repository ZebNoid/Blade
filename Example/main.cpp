#include <iostream>

#include "blade.h"

using namespace Blade;


class Sandbox : public App
{

    WindowProps wProp = {
        .title = "Blade",
        .position = {3200, 600},
    };

protected:
    auto ui() -> void override
    {
        Blade::Debug::debug = false;
        // .set({.layout = {.margin = 8,}})

        // window(contentFlex()).set(wProp);

        // window(Label("132")).set(wProp);

        // window(
        //     Row(
        //         // TextField()
        //         // .set({.layout = {.padding = 8, .flex = 1,}})
        //         // .on({
        //         //     .change = [](const std::string& value)
        //         //     {
        //         //         std::cout << value << "\n";
        //         //     },
        //         // })
        //         stack1()
        //         ,stack2()
        //         ,column1()
        //     ).set({
        //         .gap = 8,
        //         .layout = {.padding = 8, .flex = 1,},
        //         .crossAxisAlignment = CrossAxisAlignment::Stretch
        //     })
        // ).set(wProp);

        window(
            Row(
                Nop("Nop")
                , Label("Label")
            )
        ).set(wProp);

        // window(contentBladeDemo()).id(windowId).set({
        //     .title = "Blade",
        //     .size = {800, 600},
        //     .position = {3200,600},
        // });
    }

    auto stack1() -> auto
    {
        return
            Stack(
                Button("Test0").set({.layout = {.margin = 16,}})
                , Button("Test1").set({.layout = {.margin = 32,}})
                , Button("Test2").set({.layout = {.margin = 48,}})

                , Label("|-----+-----|").set({.layout = {.margin = 64,}})
                // ,Label("|---+---|").set({.layout = {.margin = 16,}})
                // ,Label("|-+-|").set({.layout = {.margin = 32,}})
            ).set({.layout = {.padding = 8, .flex = 1,}});
    }

    auto stack2() -> auto
    {
        return
            Stack(
                Label("|-----+-----|").set({.layout = {.padding = 8,}}),
                Label("|---+---|").set({.layout = {.padding = 16,}})
                // Label("|-+-|").set({.layout = {.padding = 24,}})
            ).set({.layout = {.margin = 8, .padding = 8, .flex = 1,}});
    }

    auto column1() -> auto
    {
        return
            Column(
                Button("Test2").set({.layout = {.margin = 16, .padding = 16, .flex = 1,}}),
                Button("Test1").set({.layout = {.margin = 16, .padding = 16, .flex = 1,}}),
                Button("Callback!").set({.layout = {.margin = 8, .padding = 8, .flex = 1,}}).on({
                    .click = []
                    {
                        std::cout << "!!!\n";
                    }
                }),
                Label("TTTTTT")
            ).set({
                .gap = 8,
                .layout = {.margin = 8, .padding = 8, .flex = 1,},
                .mainAxisAlignment = MainAxisAlignment::Center,
                .crossAxisAlignment = CrossAxisAlignment::Stretch,
            });
    }

    auto contentBladeDemo() -> auto
    {
        return Column(
                Label("Blade Example").id(labelId),
                TextField("Default text").set({
                    .layout = layoutMarginH,
                    .textAlign = TextAlign::Start,
                }).id(textFieldId),
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
                //  Row(
                //      Slider(50).set({.layout = {.flex=1}})
                // ).set({
                //     .layout = layoutMarginH,
                //     .mainAxisAlignment = MainAxisAlignment::Center,
                //     .crossAxisAlignment = CrossAxisAlignment::Stretch,
                // }),
                Slider(50),
                Button("Button"),
                Label("Flex").set({.layout = {.flex = 1}}),
                Row(
                    Button("Debug"),
                    // .onClick([]
                    // {
                    //     Blade::Debug::debug = !Blade::Debug::debug;
                    // }),
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
