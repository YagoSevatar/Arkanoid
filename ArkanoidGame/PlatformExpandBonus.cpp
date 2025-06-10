#include "PlatformExpandBonus.h"

namespace ArkanoidGame {
    PlatformExpandBonus::PlatformExpandBonus(const sf::Vector2f& position, Platform& platform)
        : Bonus(Type::PlatformExpand, position), m_platform(platform) {
    }

    void PlatformExpandBonus::Apply() {
        m_originalWidth = m_platform.GetRect().width;
        m_platform.SetSize(m_originalWidth * 1.5f, PLATFORM_HEIGHT);
    }

    void PlatformExpandBonus::Remove() {
        m_platform.SetSize(m_originalWidth, PLATFORM_HEIGHT);
    }
}