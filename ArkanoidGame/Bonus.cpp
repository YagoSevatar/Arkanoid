#include "Bonus.h"
#include "Platform.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
    Bonus::Bonus(Type type, const sf::Vector2f& position) :
        type(type)
    {
        shape.setRadius(BONUS_SIZE / 2.0f);
        shape.setOrigin(BONUS_SIZE / 2.0f, BONUS_SIZE / 2.0f);
        shape.setPosition(position);
        shape.setOutlineThickness(2.0f);
        shape.setOutlineColor(sf::Color::White);
    }

    void Bonus::Update(float deltaTime)
    {
        if (!shouldRemove)
        {
            if (elapsedTime > 0.0f) 
            {
                elapsedTime += deltaTime;
                if (elapsedTime >= duration)
                {
                    Remove();
                    shouldRemove = true;
                }
            }
            else 
            {
                shape.move(0, fallSpeed * deltaTime);
            }
        }
    }
    void Bonus::Draw(sf::RenderWindow& window)
    {
        if (!shouldRemove && elapsedTime == 0.0f)
        {
            window.draw(shape);
        }
    }

    sf::FloatRect Bonus::GetRect() const
    {
        return shape.getGlobalBounds();
    }

    sf::Vector2f Bonus::GetPosition() const
    {
        return shape.getPosition();
    }

    bool Bonus::CheckCollision(const Platform& platform) const
    {
        return GetRect().intersects(platform.GetRect());
    }
}