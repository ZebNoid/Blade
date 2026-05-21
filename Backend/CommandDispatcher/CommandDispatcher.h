#pragma once
#include "Api/ApiBackend.h"


namespace Blade::Backend {


class CommandDispatcher
{
public:
    explicit CommandDispatcher(Api::ApiBackend* backend);

    auto dispatch(
        const Api::BackendCommand& command
    ) -> void;

private:
    auto create(
        const Api::BackendCommand& command
    ) -> void;

    auto attach(
        const Api::BackendCommand& command
    ) -> void;

    auto remove(
        const Api::BackendCommand& command
    ) -> void;

private:
    Api::ApiBackend* m_backend = nullptr;
};


} // namespace
