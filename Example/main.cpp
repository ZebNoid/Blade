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
                Label("Label"),
                Button("Button"),
                Checkbox("Checkbox").set({
                    .layout = {
                        .margin = {10, 0},
                    }
                }),
                Button("Button"),
                Row(
                    Button("Button"),
                    Button("Button"),
                    Button("Button")
                ).set({
                    .spacing = 5,
                    .layout = {
                        .margin = {5, 0},
                    }
                }),
                Button("Button"),
                Button("Button"),
                Button("Button").set({
                    .layout = {
                        .margin = 20,
                    }
                }),
                Button("Button")
            )
            .set({
                .spacing = 10
            })
        ).set({
            .title = "Blade",
            .size = {800, 600},
            .padding = 15
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
