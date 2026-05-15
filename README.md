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
    Window* mainWindow;

public:
    Sandbox()
    {
        mainWindow = &window(
                Column(
                    Row(
                        Button("Test 1"),
                        Button("Test 1"),
                        TextField()
                    ),
                    Label("Label           Long           Test"),
                    TextField().onChange([&](const std::string& value)
                    {
                        mainWindow->title(value);
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
            )
            .title("Blade Example ")
            .size({800, 600});
    }
};


auto main() -> int
{
    std::cout << "Welcome to a WinAPI Hell! " << "\n";

    Sandbox app;
    app.Run();

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
