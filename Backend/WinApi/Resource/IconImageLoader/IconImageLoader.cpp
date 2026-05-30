#include "IconImageLoader.h"

#include "Logging/Logger.h"

namespace Blade::Backend {

auto IconImageLoader::Load(const Api::Text& path, int width, int height) -> HICON
{
    auto icon = static_cast<HICON>(LoadImage(nullptr, path.c_str(), IMAGE_ICON, width, height, LR_LOADFROMFILE));

    if (!icon)
    {
        LOGF_E(L"[Error] ImageLoader::LoadImage failed [%lu] %s", GetLastError(), path.c_str());
    }

    return icon;
}

} // namespace Blade::Backend
