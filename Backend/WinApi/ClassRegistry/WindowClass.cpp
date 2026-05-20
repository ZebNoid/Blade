#include "WindowClass.h"


namespace Blade::Backend {


auto WindowClass::Init(const HINSTANCE hInstance) -> void
{
    if (m_hInstance != nullptr) return;
    m_hInstance = hInstance;
}

auto WindowClass::Get(const std::wstring& className) -> const wchar_t*
{
    const auto it = m_names.find(className);
    if (it == m_names.end())
    {
        std::wcerr << "[Error] WindowClass::Get[" << className << "] " << "not found" << std::endl;
        return nullptr;
    }
    return it->c_str();
}

auto WindowClass::Register(const std::wstring& className, const ClassDesc& desc) -> void
{
    if (m_hInstance == nullptr) return;

    // already registered
    if (m_names.contains(className)) return;

    WNDCLASSW wc{};
    wc.lpfnWndProc = desc.proc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = className.c_str();
    wc.hCursor = desc.cursor ? desc.cursor : LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = desc.icon;
    // COLOR_WINDOW || COLOR_HIGHLIGHTTEXT
    wc.hbrBackground = desc.background != nullptr ? desc.background : (HBRUSH)(COLOR_WINDOW);
    wc.style = desc.style;

    if (!RegisterClassW(&wc))
    {
        std::wcerr << "[Error] WindowClass::Register[" << className << "] " << GetLastError() << std::endl;
        return;
    }

    m_names.insert(className);
}


} // namespace
