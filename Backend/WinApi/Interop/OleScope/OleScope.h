#pragma once

#include <ole2.h>
#include <windows.h>

namespace Blade::Backend {

class OleScope
{
public:
    OleScope() = default;
    ~OleScope();

    auto init() -> void;
    auto ok() const -> bool;
    auto result() const -> HRESULT;

private:
    HRESULT m_result = E_UNEXPECTED;
    bool m_initialized = false;
};

} // namespace Blade::Backend
