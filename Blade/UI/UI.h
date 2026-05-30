#pragma once

#include "Common/Types.h"

namespace Blade {

class UI
{
public:
    static auto Show(Api::Id id) -> void;
    static auto Hide(Api::Id id) -> void;
    static auto Unmount(Api::Id id) -> void;

    class Window
    {
    public:
        static auto Close(Api::Id id) -> void;
        static auto Minimize(Api::Id id) -> void;
        static auto Maximize(Api::Id id) -> void;
        static auto Restore(Api::Id id) -> void;
    };

    class Tray
    {
    public:
        static auto Icon(Api::Id id, Api::Text icon) -> void;
        static auto Title(Api::Id id, Api::Text title) -> void;
    };

private:
    static auto Send(Api::AppCommand command) -> void;
};

} // namespace Blade
