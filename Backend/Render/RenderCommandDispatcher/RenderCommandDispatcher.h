#pragma once

#include "Render/RenderCommand.h"

namespace Blade::Backend {

class AppBackend;

class RenderCommandDispatcher
{
public:
    explicit RenderCommandDispatcher(AppBackend* backend);

    auto dispatch(const Api::RenderCommand& command) -> void;

private:
    AppBackend* m_backend = nullptr;
};

} // namespace Blade::Backend
