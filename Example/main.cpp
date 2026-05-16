#include <iostream>

#include "blade.h"

using namespace Blade;


class Sandbox : public App
{
protected:
    auto ui() -> void override
    {
        window(
            Column(
                Label("Blade Example"),
                Label("Radio Buttons"),
                Row(
                    RadioButton("RadioButton"),
                    RadioButton("RadioButton"),
                    RadioButton("RadioButton")
                ).set({
                    .spacing = 8,
                    .layout = {
                        .margin = {8, 0},
                    }
                }),
                Label("Row Buttons"),
                Row(
                    Button("Button"),
                    Button("Button"),
                    Button("Button")
                ).set({
                    .spacing = 8,
                    .layout = {
                        .margin = {8, 0},
                    }
                }),
                Label("Checkboxes"),
                Row(
                    Checkbox("Checkbox"),
                    Checkbox("Checkbox"),
                    Checkbox("Checkbox")
                ).set({
                    .layout = {
                        .margin = {8, 0},
                    }
                }),
                Button("Button"),
                Button("Button"),
                Button("Button h margin").set({
                    .layout = {
                        .margin = {8,0},
                    }
                }),
                Button("Button")
            )
            .set({
                .spacing = 8
            })
        ).set({
            .title = "Blade",
            .size = {800, 600},
            .padding = 16
        });
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
