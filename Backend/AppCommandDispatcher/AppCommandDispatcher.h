#pragma once

#include "Command/AppCommand.h"

namespace Blade::Backend {

class AppBackend;

class AppCommandDispatcher
{
public:
    explicit AppCommandDispatcher(AppBackend* backend);

    auto dispatch(const Api::AppCommand& command) -> void;

private:
    AppBackend* m_backend = nullptr;
};

} // namespace Blade::Backend
