#include "PlatformShrinkBonus.h"

namespace ArkanoidGame {
    PlatformShrinkBonus::PlatformShrinkBonus(const sf::Vector2f& position, Platform& platform)
        : Bonus(Type::PlatformShrink, position), m_platform(platform) {
    }

    void PlatformShrinkBonus::Apply() {
        m_originalWidth = m_platform.GetRect().width;
        m_platform.SetSize(m_originalWidth * 0.7f, PLATFORM_HEIGHT);
    }

    void PlatformShrinkBonus::Remove() {
        m_platform.SetSize(m_originalWidth, PLATFORM_HEIGHT);
    }
}