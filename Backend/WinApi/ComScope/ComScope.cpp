#include "ComScope.h"


namespace Blade::Backend {

ComScope::ComScope()
    : m_result(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED))
{
}

ComScope::~ComScope()
{
    if (m_result == S_OK || m_result == S_FALSE)
    {
        CoUninitialize();
    }
}

auto ComScope::ok() const -> bool
{
    return SUCCEEDED(m_result) || m_result == RPC_E_CHANGED_MODE;
}

auto ComScope::result() const -> HRESULT
{
    return m_result;
}

} // namespace Blade::Backend
