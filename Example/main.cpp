#include <iostream>

#include "blade.h"


class Sandbox : public App
{
public:
    auto ui() -> void override
    {
        window(
            Column(
                Label("Hello"),
                Button("Test 1")
            )
        ).set({
            .title = "Blade",
            .size = {800, 600}
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
