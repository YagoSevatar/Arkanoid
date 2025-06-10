#pragma once
#include "GameObject.h"
#include "GameSettings.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
    class Platform; 

    class Bonus : public GameObject
    {
    public:
        enum class Type
        {
            FireBall,
            PlatformExpand,
            PlatformShrink,
            ExtraLife,
            Count
        };

        Bonus(Type type, const sf::Vector2f& position);
        virtual ~Bonus() = default;

        Type getType() const { return type; }
        virtual void Apply() = 0;
        virtual void Remove() = 0;
        virtual bool ShouldRemove() const { return shouldRemove; }

        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        sf::FloatRect GetRect() const override;
        sf::Vector2f GetPosition() const override;

        bool CheckCollision(const Platform& platform) const;

        static sf::Color GetColorForType(Type type) {
            switch (type) {
            case Type::FireBall: return sf::Color::Red;
            case Type::PlatformExpand: return sf::Color::Green;
            case Type::PlatformShrink: return sf::Color::Blue;
            case Type::ExtraLife: return sf::Color::Yellow;
            default: return sf::Color::White;
            }
        }

        sf::CircleShape& GetShape() { return shape; }
        const sf::CircleShape& GetShape() const { return shape; }

    protected:
        Type type;
        sf::CircleShape shape;
        float fallSpeed = 150.f;
        bool shouldRemove = false;
        float duration = 5.0f; // Длительность эффекта в секундах
        float elapsedTime = 0.0f;
    };
}