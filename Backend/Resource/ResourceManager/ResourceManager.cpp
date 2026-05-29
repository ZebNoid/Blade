#include "ResourceManager.h"

#include "WinApi/Resource/FontApi/FontApi.h"

namespace Blade::Backend {

ResourceManager::~ResourceManager()
{
    if (m_defaultFontOwned) FontApi::Destroy(m_defaultFont);
}

auto ResourceManager::defaultFont() -> HFONT
{
    if (!m_defaultFont)
    {
        m_defaultFont = FontApi::CreateMessageFont();
        m_defaultFontOwned = m_defaultFont != nullptr;
    }

    if (!m_defaultFont) m_defaultFont = FontApi::DefaultGuiFont();

    return m_defaultFont;
}

} // namespace Blade::Backend
