#include <iostream>

#include "blade.h"

using namespace Blade;


class Sandbox : public App
{
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

protected:
    auto contentFlex() -> Widget&&
    {
        return Column(
            Label("Header"),

            Label("Content").set({
                .layout = {
                    .flex = 1
                }
            }),

            Label("Footer")
        );
    }

    auto ui() -> void override
    {
        // window(contentFlex()); // TODO fix

        window(
            Column(
                Button("Header"),

                Label("Content").set({
                    .layout = {
                        .flex = 1
                    }
                }),

                Label("Footer")
            ).set({
                .mainAxisAlignment = MainAxisAlignment::Center,
                .crossAxisAlignment = CrossAxisAlignment::Stretch,
            })
        ).set({
            .title = "Test"
        });

        /*
                window(
                    Column(
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
                        Button("Button"),
                        Button("Button margin").set({
                            .layout = layoutMarginH,
                        }),
                        Button("Button")
                    )
                    .set({
                        .gap = gap,
                        .mainAxisAlignment = MainAxisAlignment::Start,
                        .crossAxisAlignment = CrossAxisAlignment::Stretch,
                    })
                ).id(windowId).set({
                    .title = "Blade",
                    .size = {800, 600},
                    .padding = 16,
                });
                /**/
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
