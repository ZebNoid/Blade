#include "ImageLoader.h"

#include <algorithm>
#include <wincodec.h>

#include "Common/Logger.h"


namespace Blade::Backend {

namespace {

template <typename T>
auto Release(T*& value) -> void
{
    if (value)
    {
        value->Release();
        value = nullptr;
    }
}

struct WicImage
{
    IWICImagingFactory* factory = nullptr;
    IWICBitmapDecoder* decoder = nullptr;
    IWICBitmapFrameDecode* frame = nullptr;
    IWICBitmapScaler* scaler = nullptr;
    IWICFormatConverter* converter = nullptr;

    ~WicImage()
    {
        Release(converter);
        Release(scaler);
        Release(frame);
        Release(decoder);
        Release(factory);
    }
};

class ComScope
{
public:
    ComScope() : m_result(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED))
    {
    }

    ~ComScope()
    {
        if (m_result == S_OK || m_result == S_FALSE)
        {
            CoUninitialize();
        }
    }

    auto ok() const -> bool
    {
        return SUCCEEDED(m_result) || m_result == RPC_E_CHANGED_MODE;
    }

    auto result() const -> HRESULT
    {
        return m_result;
    }

private:
    HRESULT m_result = S_OK;
};

auto HasExtension(const Api::Text& path, const Api::Text& extension) -> bool
{
    if (path.size() < extension.size())
    {
        return false;
    }

    return std::equal(extension.rbegin(), extension.rend(), path.rbegin(), [](wchar_t left, wchar_t right)
    {
        return towlower(left) == towlower(right);
    });
}

auto CreateBitmapMask(int width, int height) -> HBITMAP
{
    return CreateBitmap(width, height, 1, 1, nullptr);
}

auto Exists(const Api::Text& path) -> bool
{
    const auto attributes = GetFileAttributesW(path.c_str());
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

auto LogFailed(const wchar_t* operation, HRESULT result, const Api::Text& path) -> void
{
    LOGF_E(L"[Error] ImageLoader::%s failed [%08X] %s", operation, static_cast<unsigned>(result), path.c_str());
}

auto LoadBitmapFromWic(const Api::Text& path, int width, int height) -> HBITMAP
{
    ComScope com;

    if (!com.ok())
    {
        LogFailed(L"CoInitializeEx", com.result(), path);
        return nullptr;
    }

    WicImage image;

    auto result = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&image.factory));
    if (FAILED(result))
    {
        LogFailed(L"CoCreateInstance", result, path);
        return nullptr;
    }

    result = image.factory->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &image.decoder);
    if (FAILED(result))
    {
        LogFailed(L"CreateDecoderFromFilename", result, path);
        return nullptr;
    }

    result = image.decoder->GetFrame(0, &image.frame);
    if (FAILED(result))
    {
        LogFailed(L"GetFrame", result, path);
        return nullptr;
    }

    result = image.factory->CreateBitmapScaler(&image.scaler);
    if (FAILED(result))
    {
        LogFailed(L"CreateBitmapScaler", result, path);
        return nullptr;
    }

    result = image.scaler->Initialize(image.frame, width, height, WICBitmapInterpolationModeFant);
    if (FAILED(result))
    {
        LogFailed(L"InitializeScaler", result, path);
        return nullptr;
    }

    result = image.factory->CreateFormatConverter(&image.converter);
    if (FAILED(result))
    {
        LogFailed(L"CreateFormatConverter", result, path);
        return nullptr;
    }

    result = image.converter->Initialize(image.scaler, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
    if (FAILED(result))
    {
        LogFailed(L"InitializeConverter", result, path);
        return nullptr;
    }

    BITMAPINFO info{};
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    auto bitmap = CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, &bits, nullptr, 0);

    if (!bitmap || !bits)
    {
        LOGF_E(L"[Error] ImageLoader::CreateDIBSection failed [%lu] %s", GetLastError(), path.c_str());
        DeleteObject(bitmap);
        return nullptr;
    }

    result = image.converter->CopyPixels(nullptr, width * 4, width * height * 4, static_cast<BYTE*>(bits));
    if (FAILED(result))
    {
        LogFailed(L"CopyPixels", result, path);
        DeleteObject(bitmap);
        return nullptr;
    }

    return bitmap;
}

auto LoadIconFromWic(const Api::Text& path, int width, int height) -> HICON
{
    auto color = LoadBitmapFromWic(path, width, height);

    if (!color)
    {
        return nullptr;
    }

    auto mask = CreateBitmapMask(width, height);

    if (!mask)
    {
        LOGF_E(L"[Error] ImageLoader::CreateBitmapMask failed [%lu] %s", GetLastError(), path.c_str());
        DeleteObject(color);
        return nullptr;
    }

    ICONINFO info{};
    info.fIcon = TRUE;
    info.hbmColor = color;
    info.hbmMask = mask;

    auto icon = CreateIconIndirect(&info);
    DeleteObject(color);
    DeleteObject(mask);

    if (!icon)
    {
        LOGF_E(L"[Error] ImageLoader::CreateIconIndirect failed [%lu] %s", GetLastError(), path.c_str());
    }

    return icon;
}

} // namespace

auto ImageLoader::LoadIcon(const Api::Text& path, int width, int height) -> HICON
{
    if (path.empty())
    {
        return nullptr;
    }

    if (!Exists(path))
    {
        LOGF_E(L"[Error] ImageLoader::LoadIcon file not found %s", path.c_str());
        return nullptr;
    }

    if (HasExtension(path, L".ico"))
    {
        auto icon = static_cast<HICON>(LoadImage(nullptr, path.c_str(), IMAGE_ICON, width, height, LR_LOADFROMFILE));

        if (!icon)
        {
            LOGF_E(L"[Error] ImageLoader::LoadImage failed [%lu] %s", GetLastError(), path.c_str());
        }

        return icon;
    }

    return LoadIconFromWic(path, width, height);
}

} // namespace Blade::Backend
