#include "body.hpp"

#include "../core/core_settings.hpp"

Body::Body(const sf::Vector2f& position, float mass, float radius, const sf::Color& color)
    : m_position(position)
    , m_velocity(0.f, 0.f)
    , m_mass(mass)
    , m_radius(radius)
    , m_shape(radius)
    , m_trail_enabled(true)
{
    m_shape.setFillColor(color);
    m_shape.setOrigin(sf::Vector2f(radius, radius));
    m_shape.setPosition(m_position);
}

void Body::Update(sf::Time deltaTime)
{
    float dt = deltaTime.asSeconds();

    m_position += m_velocity * dt;
    m_shape.setPosition(m_position + m_camera_offset);

    if (m_trail_enabled)
    {
        for (auto &particle : m_trail_particles)
        {
            particle.update(deltaTime);
        }

        m_trail_particles.erase(
            std::remove_if(
                m_trail_particles.begin(),
                m_trail_particles.end(),
                [](const Particle &p)
                { return !p.isAlive(); }),
            m_trail_particles.end());

        m_trail_particles.emplace_back(m_position + m_camera_offset, m_radius * 0.3f, 1.f);
    }
}

void Body::Render(sf::RenderWindow& window) const
{
    if (m_trail_enabled)
    {
        for (const auto &particle : m_trail_particles)
        {
            particle.render(window);
        }
    }

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
    const float G = Settings::GravityConstant;

    sf::Vector2f r = other.m_position - m_position;

    const float eps2 = 25.f;
    float d2 = r.x*r.x + r.y*r.y + eps2;

    float invD = 1.f / std::sqrt(d2);
    sf::Vector2f dir = r * invD;

    float forceMagnitude = G * (m_mass * other.m_mass) / d2;
    sf::Vector2f force = dir * forceMagnitude;

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

void Body::SetCameraOffset(const sf::Vector2f& offset)
{
    m_camera_offset = offset;
}

void Body::EnableTrail(bool enable)
{
    m_trail_enabled = enable;
}

void Body::ClearTrail()
{
    m_trail_particles.clear();
}

const sf::Vector2f& Body::GetPosition() const
{
    return m_position;
}

float Body::GetMass() const
{
    return m_mass;
}