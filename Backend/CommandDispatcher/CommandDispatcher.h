#pragma once
#include "Api/ApiBackend.h"


namespace Blade::Backend {

class AppBackend;


class CommandDispatcher
{
public:
    explicit CommandDispatcher(AppBackend* backend);

    auto dispatch(
        const Api::ElementCommand& command
    ) -> void;

private:
    auto create(
        const Api::ElementCommand& command
    ) -> void;

    auto attach(
        const Api::ElementCommand& command
    ) -> void;

    auto remove(
        const Api::ElementCommand& command
    ) -> void;

    auto update(
        const Api::ElementCommand& command
    ) -> void;

private:
    AppBackend* m_backend = nullptr;
};


} // namespace
