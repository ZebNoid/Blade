#pragma once

#include <windows.h>


namespace Blade::Backend {

class ComScope
{
public:
    ComScope();

    ~ComScope();

    auto ok() const -> bool;

    auto result() const -> HRESULT;

private:
    HRESULT m_result = S_OK;
};

} // namespace Blade::Backend
