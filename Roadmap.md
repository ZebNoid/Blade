# Blade Roadmap

This file keeps the project direction visible. It is not a micro-task list.

## Current Focus

- [ ] Continue reorganizing overloaded `Api/Common` into focused API folders.
- [ ] Add future render backends with proper surfaces/layers.
- [ ] Move from a simple native-widget wrapper toward a declarative UI runtime.
- [x] Add backend-specific widget bindings.
- [x] Use stable API widget identities.
- [x] Support modifier-based layout and render behavior.
- [x] Keep the current WinAPI backend as a fallback backend.

## Architecture Direction

- [ ] Keep backend-specific limitations out of the public API unless the feature is explicitly backend-specific.
- [ ] Prefer namespace-scoped functions over stateless helper wrapper classes where it keeps code simple; migrate existing helpers gradually and only where it reduces noise.
- [x] Use TODO markers for long-lived transition points:
  - `// TODO deprecated`
  - `// TODO refactor`
  - `// TODO change`
  - `// TODO fix`
- [x] `Backend` owns native widgets, platform resources, message routing, and actual rendering.
- [x] `Blade` owns widget trees, normalization, layout, materialization, events, and render command generation.
- [x] `Api` defines the public declarative model and stable identifiers.

## Widget Identity And Binding

API widget types should not be free-form strings. Blade uses stable `Api::WidgetType` ids for declarative widget identity.

Backends may implement the same API widget with different native/custom components.

```cpp
Api::WidgetTypes::Button -> Api::ComponentTypes::Button
Api::WidgetTypes::Button -> Backend::UI::Surface
Api::WidgetTypes::Label  -> Api::ComponentTypes::Label
```

- [ ] Keep debug names separate from runtime ids.
- [ ] Allow overriding mappings with non-standard backend components, such as `Button -> Surface`.
- [x] Organize backend component files into system/root, native controls, and custom surfaces.
- [x] Map `ContextArea` to universal `Surface` instead of a dedicated backend component.
- [x] Prioritize root component ids before controls, such as `Window`, `Tray`, then `Button`.
- [x] Move `WidgetType` and `ComponentType` from `Api/Common` to `Api/Widget`.
- [x] Add `Api::ComponentType` for backend component identity.
- [x] Add public `Backend::UI::*` aliases for standard backend component ids.
- [x] Add default binding and supported component introspection on backend.
- [x] Let backend provide default API-widget-to-component bindings.
- [x] Add `NativeBindingRegistry`.
- [x] Register current backend factories by `Api::WidgetType`.
- [x] Replace `WidgetTree.type`, `LayoutNode.type`, `ElementCommand.nodeType`, and `NativeNode.type` string routing with `Api::WidgetType`.
- [x] Add `Api::WidgetType`.

## Render Pipeline

Modifiers should produce render commands independently from native widget creation.

Render definitions should be stored as flat command sequences per widget state:

- normal;
- hover;
- focus;
- pressed;
- disabled;
- dragOver.

- [ ] Introduce a render context so `RenderApi` does not depend on `ResourceManager` directly.
- [ ] Introduce proper render surfaces/layers.
- [ ] Allow static virtual elements such as labels to opt out of hit-testing and pass input to elements behind them.
- [ ] Make modifier chains like `padding().background().padding().background()` semantically correct.
- [ ] Move away from sibling child `HWND` composition limitations.
- [x] Support hover and dragOver state for window-level virtual surfaces.
- [x] Support context menus for window-level virtual surfaces and areas.
- [x] Support basic render state switching for custom-based widgets.
- [x] Move window-level virtual paint and event routing out of `NativeNodeFactory`.
- [x] Add custom render `Surface`.
- [x] Cache GDI+ brushes and pens for fallback custom rendering.
- [x] Add GDI+ fallback custom rendering for anti-aliased shapes.
- [x] Cache GDI resources in `ResourceManager` instead of creating brushes/pens during paint.
- [x] Support background, border radius, border color, and text color.
- [x] Let `RenderSurface` and `LabelSurface` consume render definitions.
- [x] Add render commands and backend render registry.
- [x] Keep the current WinAPI render path as fallback.

## Modifier Model

Widget-specific properties should stay as explicit widget API.

Common visual/layout behavior should move toward fluent modifier methods:

```cpp
Label(L"text")
    .padding(8)
    .background(Api::Color::Green())
    .borderRadius(8)
    .states({
        .hover = Api::Modifier().background(Api::Color::Red())
    });
```

- [ ] Keep `.set(...)` / `.on(...)` only where fluent API is not complete yet.
- [ ] Mark transition-only API with `// TODO deprecated` when fluent replacements exist.
- [x] Remove margin from layout model.
- [x] Split layout-affecting modifiers from render modifiers.
- [x] Add modifier chain.

## Layout

Layout runtime should remain responsible only for layout calculation and layout-driven updates.

Render and events should stay outside layout runtime except where layout size/position affects them.

- [ ] Revisit virtual wrapper behavior once render surfaces exist.
- [ ] Add widget `minSize` / `maxSize` modifiers and define how constraints interact with flex, padding, and parent layout.
- [x] Keep layout engine independent from backend/native concepts.
- [x] Add virtual layout wrappers for modifier effects.
- [x] Add flex behavior.
- [x] Add `Row`, `Column`, `Stack`.
- [x] Refactor layout algorithms into smaller units.

## Widgets

Widgets should be declarative API objects. Backend implementation choice should be configurable.

Current native/custom split:

- `NativeButton` uses WinAPI `BUTTON`.
- `NativeLabel` uses WinAPI `STATIC`.
- `LabelSurface` renders label text through the window-level surface path.
- `ImageSurface` renders images through the window-level surface path.
- Custom buttons should usually be Blade widgets built on top of `Surface`, modifiers, and events.

- [ ] Add more native common controls.
- [ ] Keep fallback native widgets available where useful.
- [x] Split system `NativeLabel` from custom-rendered `LabelSurface`.
- [x] Add `ImageSurface`.
- [x] Keep `Button` mapped to native/system button by default.
- [x] Add low-level custom render `Surface`.

## Backend Resources

Backend resources should be cached and owned by `ResourceManager`.

Hot paint paths should not repeatedly call:

- `CreateSolidBrush`;
- `CreatePen`;
- `CreateFontIndirect`;
- image/icon loading APIs.

- [ ] Keep region handling separate because `SetWindowRgn` transfers ownership to WinAPI.
- [x] Add pen cache.
- [x] Add color brush cache.

## Fallback WinAPI Backend Limitations

The current WinAPI backend is a fallback/native backend, not the final rendering model.

- [ ] Solve Stack overlay cases through proper render surfaces/layers.
- [ ] Add `DwmApi` for optional window backdrop effects, such as `.backdrop(Api::WindowBackdrop::Blur)`, ignored when unsupported by the system.
- [x] Avoid adding public API only to hide fallback backend limitations.
- [x] Track native `BUTTON` painting, hit-test, and z-order limitations.
- [x] Track rounded transparent repaint artifacts as a fallback backend limitation.
- [x] Track transparent child `HWND` composition as unreliable with sibling controls.

## Documentation

- [ ] Keep README focused on user-facing API.
- [ ] Keep architecture decisions in docs or this roadmap.
- [ ] Avoid documenting fallback backend quirks as intended public behavior.
- [x] `Docs/Architecture.md` exists.
- [x] `Docs/CodeStyleGuide.md` exists.
- [x] README contains basic examples and supported widgets/properties.

## API Structure

- [ ] Continue moving domain-specific API files out of `Api/Common`.
