#include "OleScope.h"

namespace Blade::Backend {

OleScope::~OleScope()
{
    if (m_initialized) OleUninitialize();
}

auto OleScope::init() -> void
{
    if (m_initialized) return;

    m_result = OleInitialize(nullptr);
    m_initialized = m_result == S_OK || m_result == S_FALSE;
}

auto OleScope::ok() const -> bool
{
    return SUCCEEDED(m_result);
}

auto OleScope::result() const -> HRESULT
{
    return m_result;
}

} // namespace Blade::Backend
