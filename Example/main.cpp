#include <iostream>

#include "blade.h"


class Sandbox : public App
{
public:
    Sandbox()
    {
    }

    auto build() -> void override
    {
        // window(Label("Test"));
        window(Button("Test 1"));

        // window(
        //     Column(
        //         Button("Test 1"),
        //         Label("Hello")
        //     )
        // );
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
