#pragma once
#include "Api/ApiBackend.h"
#include "Api/BackendCommand.h"


namespace Blade {


class Materializer
{
public:
    explicit Materializer(Api::ApiBackend* backend)
    {
        m_backend = backend;
    }

    auto mount(const Api::WidgetTree& tree) -> void;

    auto visit(
        const Api::WidgetTree& node,
        std::vector<Api::BackendCommand>& out,
        Api::Id parent
    ) -> void;

private:
    Api::ApiBackend* m_backend = nullptr;
};


} // namespace
