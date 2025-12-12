#pragma once

#include "trail_particle.hpp"

#include <SFML/Graphics.hpp>

class Body
{
public:
    Body(const sf::Vector2f& position, float mass, float radius, const sf::Color& color);
    ~Body() = default;

    void Update(sf::Time deltaTime);
    void Render(sf::RenderWindow& window) const;

public:
    void ApplyForce(const sf::Vector2f& force, sf::Time deltaTime);
    void ApplyGravityFromSingle(const Body& other, sf::Time deltaTime);
    void ApplyGravityFromAll(const std::vector<Body>& bodies, sf::Time deltaTime);

    [[nodiscard]] const sf::Vector2f& GetPosition() const;
    [[nodiscard]] float GetMass() const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

    float m_mass;
    float m_radius;

    sf::CircleShape m_shape;
    std::vector<Particle> m_trail_particles;
};