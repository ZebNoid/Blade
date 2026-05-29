# Architecture

Blade is split into three main modules:

```mermaid
flowchart LR
    Backend["Backend\nnative implementation"] <--> Api["Api\npublic contracts"]
    Blade["Blade\ndeclarative widgets and runtime"] <--> Api

    Blade -- "ElementCommand" --> Api
    Api -- "execute command" --> Backend
    Backend -- "BackendMessage\nresize / event" --> Api
    Api -- "dispatch callback" --> Blade
    Blade -- "AppCommand\nUI / app lifecycle" --> Api
    Api -- "execute app command" --> Backend

    linkStyle 2 stroke:#2563eb,stroke-width:2px
    linkStyle 3 stroke:#2563eb,stroke-width:2px
    linkStyle 4 stroke:#16a34a,stroke-width:2px
    linkStyle 5 stroke:#16a34a,stroke-width:2px
    linkStyle 6 stroke:#2563eb,stroke-width:2px
    linkStyle 7 stroke:#2563eb,stroke-width:2px
```

## Modules

- `Api` contains shared public contracts: commands, messages, props, events, and common data types.
- `Blade` contains user-facing widgets and runtime logic that converts widget trees into layout and backend commands.
- `Backend` contains native implementation details and executes commands through WinAPI.

## Runtime Flow

```mermaid
flowchart TD
    UserCode["User code\nWindow(...).set(...).on(...).mount(this)"]
    WidgetTree["WidgetTree\nwidgets, props, events, overlays"]
    RuntimeTree["WidgetTreeRegistry\nassign ids and keep roots"]
    LayoutPass["LayoutPass::Compute"]
    LayoutTree["LayoutNode tree"]
    LayoutEngine["LayoutEngine\nmeasure and arrange"]
    Materializer["Materializer"]
    Commands["ElementCommand list"]
    UI["UI\nruntime commands"]
    AppCommand["AppCommand"]
    Backend["Backend"]
    Messages["BackendMessage\nresize / event"]
    EventRuntime["EventRuntime\ncallbacks"]

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
    UserCode --> UI
    UI --> AppCommand
    AppCommand --> Backend
    Backend --> Messages
    Messages --> EventRuntime
    EventRuntime --> UserCode

    linkStyle 0 stroke:#444,stroke-width:1.5px
    linkStyle 1 stroke:#444,stroke-width:1.5px
    linkStyle 2 stroke:#444,stroke-width:1.5px
    linkStyle 3 stroke:#444,stroke-width:1.5px
    linkStyle 4 stroke:#444,stroke-width:1.5px
    linkStyle 5 stroke:#444,stroke-width:1.5px
    linkStyle 6 stroke:#444,stroke-width:1.5px
    linkStyle 7 stroke:#444,stroke-width:1.5px
    linkStyle 8 stroke:#2563eb,stroke-width:2px
    linkStyle 9 stroke:#2563eb,stroke-width:2px
    linkStyle 10 stroke:#2563eb,stroke-width:2px
    linkStyle 11 stroke:#2563eb,stroke-width:2px
    linkStyle 12 stroke:#2563eb,stroke-width:2px
    linkStyle 13 stroke:#16a34a,stroke-width:2px
    linkStyle 14 stroke:#16a34a,stroke-width:2px
    linkStyle 15 stroke:#16a34a,stroke-width:2px
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

    linkStyle 0 stroke:#444,stroke-width:1.5px
    linkStyle 1 stroke:#444,stroke-width:1.5px
    linkStyle 2 stroke:#444,stroke-width:1.5px
    linkStyle 3 stroke:#444,stroke-width:1.5px
    linkStyle 4 stroke:#2563eb,stroke-width:2px
    linkStyle 5 stroke:#2563eb,stroke-width:2px
    linkStyle 6 stroke:#2563eb,stroke-width:2px
    linkStyle 7 stroke:#2563eb,stroke-width:2px
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

    linkStyle 0 stroke:#444,stroke-width:1.5px
    linkStyle 1 stroke:#444,stroke-width:1.5px
    linkStyle 2 stroke:#444,stroke-width:1.5px
    linkStyle 3 stroke:#444,stroke-width:1.5px
```
