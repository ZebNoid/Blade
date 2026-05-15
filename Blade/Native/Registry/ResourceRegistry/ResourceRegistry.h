#pragma once

#include <string>
#include <unordered_map>

#include <windows.h>

class ResourceRegistry
{
public:
    static auto Init() -> void;

    static auto Shutdown() -> void;

public:
    static auto RegisterFont(
        const std::string& key,
        HFONT font
    ) -> void;

    static auto GetFont(const std::string& key) -> HFONT;

    static auto CreateSystemUIFont() -> HFONT;

private:
    static inline bool s_initialized = false;
    static inline std::unordered_map<std::string, HFONT> s_fonts;
};