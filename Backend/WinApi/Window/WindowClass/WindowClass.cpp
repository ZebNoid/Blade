#include "WindowClass.h"

#include "Common/Logger.h"


namespace Blade::Backend {

auto WindowClass::Init(const HINSTANCE hInstance) -> void
{
    if (m_hInstance != nullptr)
    {
        return;
    }

    m_hInstance = hInstance;
}

auto WindowClass::Get(const std::wstring& className) -> const wchar_t*
{
    const auto it = m_names.find(className);
    if (it == m_names.end())
    {
        LOGF_E(L"[Error] WindowClass::Get[%s] not found", className.c_str());
        return nullptr;
    }
    return it->c_str();
}

auto WindowClass::Register(const std::wstring& className, const ClassDesc& desc) -> void
{
    if (m_hInstance == nullptr)
    {
        return;
    }

    if (m_names.contains(className))
    {
        return;
    }

    WNDCLASSW wc{};
    wc.lpfnWndProc = desc.proc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = className.c_str();
    wc.hCursor = desc.cursor ? desc.cursor : LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = desc.icon;
    wc.hbrBackground = desc.background ? desc.background : reinterpret_cast<HBRUSH>(COLOR_MENU + 1);
    wc.style = desc.style;

    if (!RegisterClassW(&wc))
    {
        LOGF_E(L"[Error] WindowClass::Register[%s] %lu", className.c_str(), GetLastError());
        return;
    }

    m_names.insert(className);
}

} // namespace Blade::Backend
