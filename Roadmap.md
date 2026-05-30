# Blade Roadmap

This file keeps the project direction visible. It is not a micro-task list.

## Current Focus

- [ ] Add backend-specific widget bindings.
- [ ] Add future render backends with proper surfaces/layers.
- [ ] Move from a simple native-widget wrapper toward a declarative UI runtime.
- [x] Use stable API widget identities.
- [x] Support modifier-based layout and render behavior.
- [x] Keep the current WinAPI backend as a fallback backend.

## Architecture Direction

- [ ] Keep backend-specific limitations out of the public API unless the feature is explicitly backend-specific.
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
Api::WidgetTypes::Button -> Backend::NativeTypes::NativeButton
Api::WidgetTypes::Button -> Backend::NativeTypes::CustomButton
Api::WidgetTypes::Label  -> Backend::NativeTypes::CustomLabel
```

- [ ] Add backend-side `NativeType`.
- [ ] Add `NativeBindingRegistry`.
- [ ] Let backend provide default API-widget-to-native-widget bindings.
- [ ] Allow overriding mappings, such as `Button -> CustomButton`.
- [ ] Keep debug names separate from runtime ids.
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

- [ ] Cache GDI resources in `ResourceManager` instead of creating brushes/pens during paint.
- [ ] Introduce a render context so `RenderApi` does not create resources directly.
- [ ] Add custom-render widgets such as `CustomButton`.
- [ ] Introduce proper render surfaces/layers.
- [ ] Make modifier chains like `padding().background().padding().background()` semantically correct.
- [ ] Move away from sibling child `HWND` composition limitations.
- [x] Support basic render state switching for custom-based widgets.
- [x] Support background, border radius, border color, and text color.
- [x] Let `NativeCustom` and `NativeLabel` consume render definitions.
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
- [x] Keep layout engine independent from backend/native concepts.
- [x] Add virtual layout wrappers for modifier effects.
- [x] Add flex behavior.
- [x] Add `Row`, `Column`, `Stack`.
- [x] Refactor layout algorithms into smaller units.

## Widgets

Widgets should be declarative API objects. Backend implementation choice should be configurable.

Current native/custom split:

- `NativeButton` uses WinAPI `BUTTON`.
- `NativeLabel` is actually a custom-render label.
- Future `CustomButton` should use custom rendering and render states.

- [ ] Add `CustomButton`.
- [ ] Decide whether the public `Button` maps to `NativeButton` or `CustomButton` by backend binding.
- [ ] Keep fallback native widgets available where useful.

## Backend Resources

Backend resources should be cached and owned by `ResourceManager`.

Hot paint paths should not repeatedly call:

- `CreateSolidBrush`;
- `CreatePen`;
- `CreateFontIndirect`;
- image/icon loading APIs.

- [ ] Add color brush cache.
- [ ] Add pen cache.
- [ ] Keep region handling separate because `SetWindowRgn` transfers ownership to WinAPI.

## Fallback WinAPI Backend Limitations

The current WinAPI backend is a fallback/native backend, not the final rendering model.

- [ ] Solve Stack overlay cases through proper render surfaces/layers.
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
