#pragma once

#include <functional>
#include <optional>
#include <windows.h>


namespace Blade::Backend {


class MessageRouter
{
public:
    using MessageHandler = std::function<
        LRESULT(HWND, UINT, WPARAM, LPARAM)
    >;

    auto on(UINT msg, MessageHandler handler) -> void;

    auto dispatch(
        HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
    ) -> std::optional<LRESULT>;

private:
    std::unordered_map<UINT, MessageHandler> m_handlers;
};

} // namespace
