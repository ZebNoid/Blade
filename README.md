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
> This code written with **LLM** assistance
> 

## Example

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
            Button(L"Button").set({.isDefault = true,})
        ).set({
            .title = L"Window",
            .size = {800, 300},
            .position = {500, 400},
        }).build(this);

        Window().set({
            .title = L"Window 2",
            .size = {400, 500},
        }).build(this);
    }
};


auto main() -> int
{
    Sandbox app;
    return app.run();
}
```
