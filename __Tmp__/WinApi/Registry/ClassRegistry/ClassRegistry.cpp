#include "ClassRegistry.h"


namespace Blade::Backend {


auto ClassRegistry::Init(const HINSTANCE hInstance) -> void
{
    if (m_hInstance != nullptr) return;
    m_hInstance = hInstance;
}

auto ClassRegistry::Get(const std::string& key) -> const wchar_t*
{
    const auto it = m_names.find(key);
    if (it == m_names.end()) return L"";
    return it->second.c_str();
}

auto ClassRegistry::Register(const std::string& key, const ClassDesc& desc) -> void
{
    if (m_hInstance == nullptr) return;

    // already registered
    if (m_names.contains(key)) return;

    std::wstring className = desc.name;

    WNDCLASSW wc{};
    wc.lpfnWndProc = desc.proc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = className.c_str();
    wc.hCursor = desc.cursor ? desc.cursor : LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = desc.icon;
    // COLOR_WINDOW || COLOR_HIGHLIGHTTEXT
    wc.hbrBackground = desc.background != nullptr ? desc.background : (HBRUSH)(COLOR_WINDOW);
    wc.style = desc.style;

    RegisterClassW(&wc);

    m_names[key] = std::move(className);
}


} // namespace
