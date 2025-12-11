#include "body.hpp"

Body::Body(const sf::Vector2f& position, float mass, float radius, const sf::Color& color)
    : m_position(position)
    , m_velocity(0.f, 0.f)
    , m_mass(mass)
    , m_radius(radius)
    , m_shape(radius)
{
    m_shape.setFillColor(color);
    m_shape.setOrigin(sf::Vector2f(radius, radius));
    m_shape.setPosition(m_position);
}

void Body::Update(sf::Time deltaTime)
{
    float dt = deltaTime.asSeconds();
    m_position += m_velocity * dt;
    m_shape.setPosition(m_position);
}

void Body::Render(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void Body::ApplyForce(const sf::Vector2f& force, sf::Time deltaTime)
{
    float dt = deltaTime.asSeconds();
    sf::Vector2f acceleration = force / m_mass;
    m_velocity += acceleration * dt;
}

void Body::ApplyGravityFromSingle(const Body& other, sf::Time deltaTime)
{
    const float G = 2500.0f;

    sf::Vector2f direction = other.m_position - m_position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance == 0.f)
        return;

    sf::Vector2f normalizedDirection = direction / distance;
    float forceMagnitude = G * (m_mass * other.m_mass) / (distance * distance);
    sf::Vector2f force = normalizedDirection * forceMagnitude;

    ApplyForce(force, deltaTime);
}

void Body::ApplyGravityFromAll(const std::vector<Body>& bodies, sf::Time deltaTime)
{
    for (const auto& other : bodies)
    {
        if (&other != this)
        {
            ApplyGravityFromSingle(other, deltaTime);
        }
    }
}