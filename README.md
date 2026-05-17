# Blade 

![code](https://badges.ws/badge/license-MIT-black?&labelColor=00599C)
![llm](https://badges.ws/badge/use-LLM-black?labelColor=00599C) 
![code](https://badges.ws/badge/code-C++-black?icon=cplusplus&labelColor=00599C)
![code](https://badges.ws/badge/ide-Clion-black?icon=clion&labelColor=00599C)


<p align="center">
<img src=".github/assets/BladeLogo.svg" width="500">
</p>

> [!NOTE]
> 
> _Super_ **Fast** _Super_ **Small** _Super_ **Simple** _Super_ **Buggy**
> 
> C++ **Declarative** UI Library 
> 
> Based on **WinAPI** from *Hell*
> 

> [!IMPORTANT]
> 
> **LLM** assisted in writing this code
> 

## Example

```c++
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
                Row(
                    TextField("TextField").set({.layout = {.flex = 1,}}),
                    RadioButton("RadioButton"),
                    RadioButton("RadioButton"),
                    Checkbox("Checkbox")
                ).set({.gap = 8, .crossAxisAlignment = CrossAxisAlignment::Center,}),
                Row(
                    Progress(10).set({.layout = {.flex = 1,}}),
                    Slider(90).set({.layout = {.flex = 2,}})
                ).set({.gap = 8, .crossAxisAlignment = CrossAxisAlignment::Center,}),
                Column().set({.layout = {.flex = 1,},}),
                Label("Footer")
            ).set({
                .gap = 8,
                .layout = {.padding = 8,},
                .crossAxisAlignment = CrossAxisAlignment::Stretch,
            })
        ).set({
            .title = "Blade",
            .size = {800, 600},
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
```


## User Space

```
App
│
└── Window > (NativeWindow)

Widget
│
├── Label > (NativeLabel)
├── Button > (NativeButton)
├── RadioButton > (NativeRadioButton)
├── Checkbox > (NativeCheckbox)
├── Progress > (NativeProgress)
├── Slider > (NativeSlider)
├── TextField > (NativeTextField)
│
└── Container
	├── Stack
	├── Colum
	└── Row
```

## Backend

```
Backend
│    
└── NativeWidget
    │
	├── NativeWindow
	├── NativeLabel
	├── NativeButton
	├── NativeRadioButton
	├── NativeCheckbox
	├── NativeProgress
	├── NativeSlider
	└── NativeTextField
```
