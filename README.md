# Blade 

![code](https://badges.ws/badge/License-MIT-black?&labelColor=00599C)
![llm](https://badges.ws/badge/LLM-Codex-black?labelColor=00599C) 
![code](https://badges.ws/badge/Code-C++-black?icon=cplusplus&labelColor=00599C)
![code](https://badges.ws/badge/Ide-Clion-black?icon=clion&labelColor=00599C)


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
> This code written with **LLM** assistance
> 

```c++
#include "blade.h"
#include "App/AppBackend.h"

using namespace Blade;

class Sandbox : public App
{
protected:
    auto onSetup() -> void override
    {
        use<Backend::AppBackend>();
    }

    auto onCreate() -> void override
    {
        Window(
            Button(L"Quit")
                .onClick([] {
                    App::Quit();
                })
        )
            .title(L"Hello Blade")
            .size({400, 200})
            .placement(Api::WindowPlacement::Center())
            .mount();
    }
};

auto main() -> int
{
    Sandbox app;
    return app.run();
}
```

## Content

<details>
<summary>Show navigation</summary>

- [Application](#application)
- [Runtime UI Commands](#runtime-ui-commands)
- [Syntax](#syntax)
- [Common Modifiers](#common-modifiers)
- [Root Widgets](#root-widgets)
  - [Window](#window)
    - [Window Methods](#window-methods)
    - [WindowPlacement Factories](#windowplacement-factories)
  - [Tray](#tray)
    - [Tray Methods](#tray-methods)
- [Controls](#controls)
  - [Button](#button)
    - [Button Methods](#button-methods)
  - [Label](#label)
    - [Label Methods](#label-methods)
  - [Image](#image)
    - [Image Methods](#image-methods)
- [Menu](#menu)
  - [Menu Separator](#menu-separator)
  - [Submenu](#submenu)
  - [Menu Methods](#menu-methods)
  - [MenuTrigger Values](#menutrigger-values)
  - [MenuItem Methods](#menuitem-methods)
  - [Shortcut Factories](#shortcut-factories)
- [Layout](#layout)
  - [Column](#column)
  - [Row](#row)
  - [Stack](#stack)
  - [Layout Methods](#layout-methods)

</details>

## Application

Blade apps inherit from `Blade::App`. Use `onSetup()` to select a backend and `onCreate()` to create root widgets.

`App` owns application lifecycle. `App::Quit()` stops the application message loop and can be called from callbacks.

## Runtime UI Commands

Use `UI` to send runtime commands to already mounted UI elements by id.

```c++
auto windowId = Window(...).mount();
auto trayId = Tray(...).mount();

UI::Show(windowId);
UI::Hide(windowId);
UI::Unmount(windowId);

UI::Window::Close(windowId);
UI::Window::Minimize(windowId);
UI::Window::Maximize(windowId);
UI::Window::Restore(windowId);

UI::Tray::Icon(trayId, L"app.ico");
UI::Tray::Title(trayId, L"Blade");
```

`Show`, `Hide`, and `Unmount` are generic UI commands. Window-only and tray-only commands live in `UI::Window` and `UI::Tray`.

## Syntax

Widgets use fluent methods for common layout, visual options, widget-specific configuration, and events.

```c++
Label(L"Status")
    .padding(8)
    .states({
        .normal = Api::Modifier().background(Api::Color::Green()),
        .hover = Api::Modifier().background(Api::Color::Red()),
    })
    .padding(16)
```

> [!CAUTION]
> Nested `.states(...)` inside `ModifierStates` branches are ignored and logged as a warning. State branches are intended to contain plain modifiers only.

Root widgets are attached to the app runtime with `.mount()`.

```c++
Window(
    Button(L"Quit")
        .onClick([] {
            App::Quit();
        })
)
    .mount();

Tray(
    Menu(
        MenuItem(L"Exit")
            .onClick([] {
                App::Quit();
            })
    )
)
    .mount();
```

## Common Modifiers

Common modifiers are available on widgets through the base fluent chain.

<details>
<summary>Common modifiers</summary>

| Method | Meaning | Example |
| --- | --- | --- |
| `size(Api::Size)` | preferred widget size | `.size({120, 40})` |
| `minSize(Api::Size)` | minimum measured size | `.minSize({80, 24})` |
| `maxSize(Api::Size)` | maximum measured size, zero axis means unconstrained | `.maxSize({240, 0})` |
| `flex(int)` | flex grow value for parent layout | `.flex(1)` |
| `visible(bool)` | initial visibility | `.visible(false)` |
| `padding(Api::Thickness)` | layout/render padding | `.padding({8})` |
| `padding(int)` | uniform padding | `.padding(8)` |
| `background(Api::Color)` | background fill | `.background(Api::Color::Hex(L"#2196F3"))` |
| `borderRadius(int)` | rounded corners | `.borderRadius(8)` |
| `borderColor(Api::Color)` | border color | `.borderColor(Api::Color::Hex(L"#0D47A1"))` |
| `color(Api::Color)` | text color | `.color(Api::Color::White())` |
| `states(Api::ModifierStates)` | state-specific modifier branches | `.states({ .hover = Api::Modifier().background(Api::Color::Hex(L"#1976D2")) })` |
| `modifier(Api::Modifier)` | append a raw modifier chain | `.modifier(Api::Modifier().padding(8))` |

</details>

## Root Widgets

### Window

```c++
Window(
    Button(L"Close")
        .onClick([] {
            App::Quit();
        })
)
    .title(L"Window")
    .size({800, 600})
    .placement(Api::WindowPlacement::Center())
    .onClose([] {
        return true;
    })
    .mount();
```

<a id="window-methods"></a>
<details>
<summary>Supported <code>Window</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `title(...)` | `Api::Text` | `.title(L"Settings")` |
| `icon(...)` | `Api::Text` | `.icon(L"app.ico")` or `.icon(L"app.png")` |
| `placement(...)` | `Api::WindowPlacementProps` | `.placement(Api::WindowPlacement::Center())` |
| `resizable(...)` | `bool`, default `true` | `.resizable(false)` |
| `topMost(...)` | `bool`, default `true` | `.topMost()` |
| `taskbar(...)` | `bool`, default `true` | `.taskbar(false)` |
| `minSize(...)` | `Api::Size` | `.minSize({320, 240})` |
| `maxSize(...)` | `Api::Size` | `.maxSize({1920, 1080})` |
| `caption(...)` | `Api::CaptionProps` | `.caption({ .visible = false })` |
| `state(...)` | `Api::WindowState` | `.state(Api::WindowState::Maximized)` |
| `lifetime(...)` | `Api::Lifetime` | `.lifetime(Api::Lifetime::Ignore)` |
| `onClose(...)` | callback, return `false` to cancel close | `.onClose([] { return true; })` |
| `onDrop(...)` | dropped file paths callback | `.onDrop([](Api::Text files) { LOG(files); })` |

</details>

<a id="windowplacement-factories"></a>
<details>
<summary><code>WindowPlacement</code> factories</summary>

```c++
Api::WindowPlacement::Manual({100, 100})
Api::WindowPlacement::Center()
Api::WindowPlacement::TopLeft()
Api::WindowPlacement::TopRight()
Api::WindowPlacement::TopFill()
Api::WindowPlacement::LeftFill()
Api::WindowPlacement::Fill()
```

Most placement factories accept offset and monitor index:

```c++
Api::WindowPlacement::Center({20, 0}, 1)
```

</details>

### Tray

`Tray` creates a system tray icon. It can be used without any windows.

```c++
Tray(
    Menu(
        MenuItem(L"Open")
            .onClick([] {
                LOG(L"Open");
            }),
        MenuItem(L"Exit")
            .onClick([] {
                App::Quit();
            })
    ).trigger(Api::MenuTrigger::LeftRight)
)
    .title(L"Blade")
    .icon(L"app.ico")
    .mount();
```

<a id="tray-methods"></a>
<details>
<summary>Supported <code>Tray</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `title(...)` | `Api::Text` | `.title(L"Blade Tray")` |
| `icon(...)` | `Api::Text` | `.icon(L"app.ico")` or `.icon(L"app.png")` |
| `lifetime(...)` | `Api::Lifetime` | `.lifetime(Api::Lifetime::Ignore)` |
| `onClick(...)` | callback | `.onClick([] { LOG(L"Tray"); })` |

</details>

## Controls

### Button

```c++
Button(L"Run")
    .size({120, 40})
    .defaultButton()
    .onClick([] {
        LOG(L"Clicked");
    })
    .onDrop([](Api::Text files) {
        LOGF_D(L"Drop:\n%s", files.c_str());
    })
```

<a id="button-methods"></a>
<details>
<summary>Supported <code>Button</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `defaultButton(...)` | `bool`, default `true` | `.defaultButton()` |
| `onClick(...)` | callback | `.onClick([] { LOG(L"Clicked"); })` |
| `onFocus(...)` | callback | `.onFocus([](bool focused) { return focused; })` |
| `onDrop(...)` | dropped file paths callback | `.onDrop([](Api::Text files) { LOG(files); })` |

</details>

### Label

```c++
Label(L"Status")
    .padding(8)
    .background(Api::Color::Hex(L"#E3F2FD"))
```

`Label` is rendered through the surface path by default.

<a id="label-methods"></a>
<details>
<summary>Supported <code>Label</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `text(...)` | `Api::Text` | `.text(L"Ready")` |

</details>

### Image

```c++
Image(L"assets/logo.png")
    .size({120, 120})
```

Use `source(...)` to change the displayed image source while building the widget.

```c++
Image(L"assets/logo.png")
    .source(L"assets/preview.png")
```

<a id="image-methods"></a>
<details>
<summary>Supported <code>Image</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `source(...)` | `Api::Text` | `.source(L"app.png")` |

</details>

## Menu

Menus are attached through `ContextArea`, `Tray`, or other widgets that support context menus.

```c++
ContextArea(
    Button(L"File")
        .flex(1),
    Menu(
        MenuItem(L"Open")
            .onClick([] {
                LOG(L"Open");
            }),
        MenuItem(L"Exit")
            .shortcut(Api::Shortcut::Ctrl(L'Q'))
            .onClick([] {
                App::Quit();
            })
    ).trigger(Api::MenuTrigger::RightClick)
)
```

### Menu Separator

```c++
Menu(
    MenuItem(L"Open")
        .onClick([] {
            LOG(L"Open");
        }),
    MenuSeparator(),
    MenuItem(L"Exit")
        .onClick([] {
            App::Quit();
        })
)
```

### Submenu

```c++
Menu(
    MenuItem(L"Export",
        MenuItem(L"PNG")
            .onClick([] {
                LOG(L"PNG");
            }),
        MenuItem(L"PDF")
            .onClick([] {
                LOG(L"PDF");
            })
    )
)
```

<a id="menu-methods"></a>
<details>
<summary>Supported <code>Menu</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `trigger(...)` | `Api::MenuTrigger` | `.trigger(Api::MenuTrigger::LeftRight)` |

</details>

<a id="menutrigger-values"></a>
<details>
<summary>Supported <code>MenuTrigger</code> values</summary>

| Value | Meaning |
| --- | --- |
| `None` | disabled |
| `LeftClick` | left mouse button |
| `MiddleClick` | middle mouse button |
| `RightClick` | right mouse button |
| `LeftRight` | left or right mouse button |
| `All` | left, middle, or right mouse button |

</details>

<a id="menuitem-methods"></a>
<details>
<summary>Supported <code>MenuItem</code> methods</summary>

| Method | Type | Example |
| --- | --- | --- |
| `shortcut(...)` | `Api::Shortcut` | `.shortcut(Api::Shortcut::Ctrl(L'Q'))` |
| `onClick(...)` | callback | `.onClick([] { App::Quit(); })` |

</details>

<a id="shortcut-factories"></a>
<details>
<summary><code>Shortcut</code> factories</summary>

```c++
Api::Shortcut::None()
Api::Shortcut::Ctrl(L'Q')
Api::Shortcut::Alt(L'X')
Api::Shortcut::Shift(L'F')
```

Currently shortcuts are displayed in the native menu. Keyboard handling is not implemented yet.

</details>

## Layout

### Column

```c++
Column(
    Label(L"Top")
        .flex(1)
        .onClick([] {
            // on click
        }),
    Button(L"Bottom")
)
    .gap(8)
    .flex(1)
```

### Row

```c++
Row(
    Button(L"One"),
    Button(L"Two")
        .flex(1)
)
    .gap(8)
```

### Stack

```c++
Stack(
    Button(L"Back"),
    Button(L"Front")
)
```

<a id="layout-methods"></a>
<details>
<summary>Supported layout methods</summary>

| Method | Applies to | Example |
| --- | --- | --- |
| `gap(...)` | `Column`, `Row` | `.gap(8)` |
| `verticalAlignment(...)` | `Column` main axis | `.verticalAlignment(MainAxisAlignment::Center)` |
| `horizontalAlignment(...)` | `Column` cross axis | `.horizontalAlignment(CrossAxisAlignment::Stretch)` |
| `horizontalAlignment(...)` | `Row` main axis | `.horizontalAlignment(MainAxisAlignment::Center)` |
| `verticalAlignment(...)` | `Row` cross axis | `.verticalAlignment(CrossAxisAlignment::Stretch)` |
| `flex(...)` | child widgets inside layout | `Button(L"Two").flex(1)` |
| `padding(...)` | widgets and layout containers | `Column(...).padding(8)` |
| `size(...)` | widgets and root widgets | `Button(L"Run").size({120, 40})` |

</details>
