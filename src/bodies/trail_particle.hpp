#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(const sf::Vector2f& position, float size, float life_expectancy);
    ~Particle() = default;

    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window) const;

    [[nodiscard]] bool isAlive() const;

private:
    sf::Vector2f m_position;
    float m_size;

    float m_life_expectancy;
    float m_age;
};