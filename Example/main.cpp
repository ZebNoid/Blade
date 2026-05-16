#include <iostream>

#include "blade.h"


class Sandbox : public App
{
protected:
    auto ui() -> void override
    {
        window(
            Column(
                Label("Hello"),
                Button("Test 1")
            )
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
