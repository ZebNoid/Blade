#pragma once

#include <string>
#include <unordered_map>

#include <windows.h>

class ResourceRegistry
{
public:
    static auto init() -> void;

    static auto shutdown() -> void;

public:
    static auto register_font(
        const std::string& key,
        HFONT font
    ) -> void;

    static auto get_font(const std::string& key) -> HFONT;

    static auto create_system_ui_font() -> HFONT;

private:
    static inline bool m_sInitialized = false;
    static inline std::unordered_map<std::string, HFONT> m_sFonts;
};