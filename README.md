# Blade 

> **WinAPI** from *Hell*

- LLM assisted  C++ UI Library based on WinAPI
- Proof of concept

## Example

```c++
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
        });
    }
};


auto main() -> int
{
    std::cout << "Welcome to a Blade! " << "\n";

    Sandbox app;
    app.run();

    return 0;
}
```


## Widget Tree

```
App
└── Window > (NativeWindow)

Widget
├── Label > (NativeLabel)
├── Button > (NativeButton)
├── TextField > (NativeTextField)
|
└── Container
	├── Colum
	└── Row

Backend        
└── NativeWidget
	├── NativeWindow
	├── NativeLabel
	├── NativeTextField
	└── NativeButton
```
