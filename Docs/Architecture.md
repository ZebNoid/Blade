# Architecture

Blade is split into three main modules:

```mermaid
flowchart LR
    Backend["Backend\nnative implementation"] <--> Api["Api\npublic contracts"]
    Blade["Blade\ndeclarative widgets and runtime"] <--> Api
```

## Modules

- `Api` contains shared public contracts: commands, messages, props, events, and common data types.
- `Blade` contains user-facing widgets and runtime logic that converts widget trees into layout and backend commands.
- `Backend` contains native implementation details and executes commands through WinAPI.

## Runtime Flow

```mermaid
flowchart TD
    UserCode["User code\nWindow(...).set(...).on(...).build(this)"]
    WidgetTree["WidgetTree\nwidgets, props, events, overlays"]
    RuntimeTree["WidgetTreeRegistry\nassign ids and keep roots"]
    LayoutPass["LayoutPass::Compute"]
    LayoutTree["LayoutNode tree"]
    LayoutEngine["LayoutEngine\nmeasure and arrange"]
    Materializer["Materializer"]
    Commands["ElementCommand list"]
    Backend["Backend"]

    UserCode --> WidgetTree
    WidgetTree --> RuntimeTree
    RuntimeTree --> LayoutPass
    LayoutPass --> LayoutTree
    LayoutTree --> LayoutEngine
    LayoutEngine --> LayoutTree
    LayoutTree --> Materializer
    RuntimeTree --> Materializer
    Materializer --> Commands
    Commands --> Backend
```

## Materializer

```mermaid
flowchart TD
    WidgetTree["WidgetTree"]
    LayoutTree["LayoutNode tree"]
    MenuMaterializer["MenuMaterializer\noverlays to ContextMenus"]
    Materializer["Materializer"]
    Create["Create command"]
    Attach["Attach command"]
    Update["Update command\nrect / size / placement"]
    Visible["Visible command\nroot widgets"]

    WidgetTree --> Materializer
    LayoutTree --> Materializer
    WidgetTree --> MenuMaterializer
    MenuMaterializer --> Materializer
    Materializer --> Create
    Materializer --> Attach
    Materializer --> Update
    Materializer --> Visible
```

## Layout Engine

```mermaid
flowchart TD
    LayoutPass["LayoutPass::Compute"]
    Builder["LayoutTreeBuilder"]
    Measure["LayoutEngine::Measure"]
    Arrange["LayoutEngine::Arrange"]
    Result["LayoutNode rects"]

    LayoutPass --> Builder
    Builder --> Measure
    Measure --> Arrange
    Arrange --> Result

    Measure --> Column["LayoutColumn"]
    Measure --> Row["LayoutRow"]
    Measure --> Stack["LayoutStack"]
    Measure --> Leaf["LayoutLeaf"]
    Measure --> Virtual["LayoutVirtual"]
```
