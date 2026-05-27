#include "ImageLoader.h"

#include <algorithm>

#include "Common/Logger.h"
#include "WinApi/Resource/IconImageLoader/IconImageLoader.h"
#include "WinApi/Resource/WicImageLoader/WicImageLoader.h"

namespace Blade::Backend {

namespace {

auto HasExtension(const Api::Text& path, const Api::Text& extension) -> bool
{
    if (path.size() < extension.size()) return false;

    return std::equal(extension.rbegin(), extension.rend(), path.rbegin(), [](wchar_t left, wchar_t right)
    {
        return towlower(left) == towlower(right);
    });
}

auto Exists(const Api::Text& path) -> bool
{
    const auto attributes = GetFileAttributesW(path.c_str());
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

} // namespace

auto ImageLoader::LoadIcon(const Api::Text& path, int width, int height) -> HICON
{
    if (path.empty()) return nullptr;

    if (!Exists(path))
    {
        LOGF_E(L"[Error] ImageLoader::LoadIcon file not found %s", path.c_str());
        return nullptr;
    }

    if (IsIcon(path)) return IconImageLoader::Load(path, width, height);

    auto icon = WicImageLoader::LoadIcon(path, width, height);
    if (icon) LOGF_D(L"ImageLoader::LoadIcon loaded \"%s\"", path.c_str());

    return icon;
}

auto ImageLoader::IsIcon(const Api::Text& path) -> bool
{
    return HasExtension(path, L".ico");
}

} // namespace Blade::Backend
