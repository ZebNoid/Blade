#pragma once

inline auto Utf8ToUtf16(const std::string_view text) -> std::wstring
{
    if (text.empty())
        return L"";

    int size =
        MultiByteToWideChar(
            CP_UTF8,
            0,
            text.data(),
            (int)text.size(),
            nullptr,
            0
        );

    std::wstring result(size, 0);

    MultiByteToWideChar(
        CP_UTF8,
        0,
        text.data(),
        (int)text.size(),
        result.data(),
        size
    );

    return result;
}

inline auto Utf16ToUtf8(const std::wstring& text) -> std::string
{
    if (text.empty())
    {
        return {};
    }

    const int size = WideCharToMultiByte(
        CP_UTF8,
        0,
        text.c_str(),
        (int)text.size(),
        nullptr,
        0,
        nullptr,
        nullptr
    );

    std::string result(size, 0);

    WideCharToMultiByte(
        CP_UTF8,
        0,
        text.c_str(),
        (int)text.size(),
        result.data(),
        size,
        nullptr,
        nullptr
    );

    return result;
}