#include "WicImageLoader.h"

#include <wincodec.h>

#include "Logging/Logger.h"
#include "WinApi/Interop/ComScope/ComScope.h"

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

auto LogFailed(const wchar_t* operation, HRESULT result, const Api::Text& path) -> void
{
    LOGF_E(L"[Error] ImageLoader::%s failed [%08X] %s", operation, static_cast<unsigned>(result), path.c_str());
}

auto CreateBitmapMask(int width, int height) -> HBITMAP
{
    return CreateBitmap(width, height, 1, 1, nullptr);
}

auto LoadBitmap(const Api::Text& path, int width, int height) -> HBITMAP
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

} // namespace

auto WicImageLoader::LoadIcon(const Api::Text& path, int width, int height) -> HICON
{
    auto color = LoadBitmap(path, width, height);
    if (!color) return nullptr;

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

} // namespace Blade::Backend
