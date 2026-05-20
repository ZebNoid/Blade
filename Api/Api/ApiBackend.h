#pragma once


namespace Blade::Api {


class ApiBackend
{
public:
    virtual ~ApiBackend() = default;

    virtual auto init() -> void = 0;

    virtual auto runApp() -> int = 0;

    virtual auto createWindow() -> void = 0;

    virtual auto quit() -> void = 0;
};


}
