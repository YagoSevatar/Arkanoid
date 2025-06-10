#pragma once
#include "Bonus.h"
#include "Platform.h"

namespace ArkanoidGame {
    class PlatformShrinkBonus : public Bonus {
    public:
        PlatformShrinkBonus(const sf::Vector2f& position, Platform& platform);
        void Apply() override;
        void Remove() override;

    private:
        Platform& m_platform;
        float m_originalWidth;
    };
}