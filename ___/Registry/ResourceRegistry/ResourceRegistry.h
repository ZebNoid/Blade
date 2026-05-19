#pragma once

#include <string>
#include <unordered_map>
#include <windows.h>


namespace Blade::Backend {


class ResourceRegistry
{
public:
    static auto Init() -> void;

    static auto Shutdown() -> void;

public:
    static auto RegisterFont(const std::string& key, HFONT font) -> void;

    static auto GetFont(const std::string& key) -> HFONT;

    static auto GetPen(const std::string& key, COLORREF color, int width) -> HPEN;

    static auto create_system_ui_font() -> HFONT;

private:
    static inline bool m_sInitialized = false;
    static inline std::unordered_map<std::string, HFONT> m_fonts;
    static inline std::unordered_map<std::string, HPEN> m_pens;
};


} // namespace
