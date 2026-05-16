# Blade 

> **WinAPI** from *Hell*

- LLM assisted  C++ UI Library based on WinAPI
- Proof of concept

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
                Label("Blade Example"),
                rowRadioButtons(),
                rowButtons(),
                rowCheckboxes().set({.layout = {.margin = {8, 0}}}),
                Button("Button"),
                Button("Button"),
                Label("").set({.layout = {.flex = 1}}),
                Button("Button")
            )
            .set({
                .gap = 8,
                .mainAxisAlignment = MainAxisAlignment::Start,
                .crossAxisAlignment = CrossAxisAlignment::Stretch,
            })
        ).set({
            .title = "Blade",
            .size = {800, 600},
        });
    }

    auto rowCheckboxes() -> auto
    {
        return Row(
            Label("Checkboxes:"),
            Checkbox("Checkbox").set({.layout = {.flex = 1}}),
            Checkbox("Checkbox").set({.layout = {.flex = 1}}),
            Checkbox("Checkbox").set({.layout = {.flex = 1}})
        );
    }

    auto rowButtons() -> auto
    {
        return Row(
            Button("RadioButton"),
            Label("Label").set({.layout = {.flex = 1}}),
            Button("RadioButton").set({.layout = {.flex = 2}}),
            Button("RadioButton")
        );
    }

    auto rowRadioButtons() -> auto
    {
        return Row(
            Label("RadioButtons:").set({.layout = {.flex = 1}}),
            RadioButton("RadioButton"),
            RadioButton("RadioButton"),
            RadioButton("RadioButton")
        );
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


## Widget Tree

```
App
└── Window > (NativeWindow)

Widget
├── Label > (NativeLabel)
├── Button > (NativeButton)
├── RadioButton > (NativeRadioButton)
├── Checkbox > (NativeCheckbox)
├── TextField > (NativeTextField)
|
└── Container
	├── Colum
	└── Row

Backend        
└── NativeWidget
	├── NativeWindow
	├── NativeLabel
	├── NativeButton
	├── NativeRadioButton
	├── NativeCheckbox
	└── NativeTextField
```
