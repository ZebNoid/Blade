# Code Style Guide

Short project rules. Prefer existing local style over adding new conventions.

## Naming

- Namespaces, types, structs, enum types, and enum values use `PascalCase`.
- Static class methods use `PascalCase`: `MaterializerCommands::Create(...)`.
- Regular class methods and free helper functions use `camelCase`: `createNode(...)`, `enableDropTarget(...)`.
- Local variables and parameters use `camelCase`.
- Private data members use `m_` + `camelCase`: `m_contextMenu`.
- Constants use `PascalCase`: `SubclassId`, `TrayCallback`.

```cpp
namespace Blade::Backend {

constexpr UINT TrayCallback = WM_APP + 1;

class NativeTray
{
public:
    static auto CreateDefault() -> NativeTray;
    auto applyProps(const Api::PropertyMap& props) -> void;

private:
    HWND m_hwnd = nullptr;
};

} // namespace Blade::Backend
```

## C++

- Use trailing return types: `auto name(...) -> Type`.
- Keep short guard clauses on one line when readable: `if (!parent) return false;`.
- Keep small lambdas and simple calls compact when they fit the line limit.
- Prefer focused helpers over large methods, but avoid tiny wrappers that hide obvious code.
- Prefer explicit project types from `Api` for public contracts.

```cpp
auto NativeButton::create(NativeWindow* parent, Api::Id id) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    return m_hwnd != nullptr;
}
```

## Files

- If a class has both `.h` and `.cpp`, place it in its own folder.
- Keep backend-specific WinAPI details in `Backend`.
- Keep public user-facing types in `Api`.
- Keep declarative widgets and runtime transformation logic in `Blade`.

```text
Backend/Components/Button/NativeButton/NativeButton.h
Backend/Components/Button/NativeButton/NativeButton.cpp
Api/Common/Size.h
Blade/Widget/Button/Button.h
```

## Comments

- Comments should explain non-obvious behavior, not restate the code.
- Temporary notes use `TODO` and should stay close to the relevant code.

```cpp
// Virtual nodes forward their layout to the first child for parent layout calculations.
if (node.layoutType == LayoutType::Virtual && node.children.size() == 1)
{
    node.layout = node.children.front().layout;
}
```
