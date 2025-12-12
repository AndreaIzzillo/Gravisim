#include "trail_particle.hpp"

Particle::Particle(const sf::Vector2f& position, float size, float life_expectancy)
    : m_position(position), m_size(size), m_life_expectancy(life_expectancy), m_age(0.0f) {}

void Particle::update(sf::Time deltaTime)
{
    m_age += deltaTime.asSeconds();

    float size_decay = m_size * (deltaTime.asSeconds() / m_life_expectancy);
    m_size = std::max(0.0f, m_size - size_decay);
}

void Particle::render(sf::RenderWindow& window) const
{
    float alpha = 1.0f - (m_age / m_life_expectancy);
    if (alpha < 0.0f) alpha = 0.0f;

    sf::CircleShape circle(m_size);
    circle.setOrigin(sf::Vector2f(m_size, m_size));
    circle.setPosition(m_position);
    circle.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(alpha * 128)));
    window.draw(circle);
}

bool Particle::isAlive() const
{
    return m_age < m_life_expectancy;
}