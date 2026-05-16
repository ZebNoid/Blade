#include <iostream>

#include "blade.h"


class Sandbox : public App
{
protected:
    auto ui() -> void override
    {
        window(
            Column(
                Label("Label"),
                Button("Button"),
                Button("Button"),
                Row(
                    Button("Button"),
                    Button("Button").set({
                        .layout = {
                            .margin = 20,
                        }
                    }),
                    Button("Button")
                )
                // // TODO not working
                // .set({
                //         .layout = {
                //             .margin = 20,
                //         }
                //     })
                ,
                Column(
                    Button("Button"),
                    Button("Button"),
                    Button("Button").set({
                        .layout = {
                            .margin = 20,
                        }
                    }),
                    Button("Button"),
                    Button("Button")
                )
                // // TODO not working
                // .set({
                //     .layout = {
                //         .margin = 20,
                //     }
                // })
                ,
                Button("Button"),
                Button("Button"),
                Button("Button").set({
                    .layout = {
                        .margin = 20,
                    }
                }),
                Button("Button"),
                Button("Button")
            )
            // .set({
            //     .layout = {
            //         .padding = 10
            //     }
            // })
        ).set({
            .title = "Blade",
            .size = {800, 600},
            .position = {3400, 400}
        });

        // window(
        //     Label("Hello")
        // ).set({
        // });
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
