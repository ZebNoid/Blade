#include <iostream>

#include "blade.h"


class Sandbox : public App
{
public:
    Sandbox()
    {
        window(
            Column(
                Row(
                    Button("Test 1"),
                    Button("Test 1"),
                    TextField()
                ),
                Label("Label           Long           Test"),
                TextField().onChange([&](const std::string& value)
                {
                    // std::cout << "TextField::text " << value << "\n";
                }).onFocus([](auto focus)
                {
                    // std::cout << "TextField::focus " << focus << "\n";
                }),
                Button("Hello"),
                Button("Привет"),
                Button("你好").onClick([&]
                {
                    Alert("No, don't do it!");
                })
            )
        ).set({
            .title = "Blade Example",
            .size = {600, 600}
        });

        window(Label("Test"));
    }

    auto build() -> void override
    {
        // возможно стоит создавать UI сдесь
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
