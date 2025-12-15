#include "body_manager.hpp"

void BodyManager::AddBody(const Body& body)
{
    m_bodies.push_back(body);
}

void BodyManager::UpdateAll(sf::Time deltaTime)
{
    for (auto& body : m_bodies)
    {
        body.ApplyGravityFromAll(m_bodies, deltaTime);
    }

    for (auto& body : m_bodies)
    {
        body.Update(deltaTime);
    }
}

void BodyManager::RenderAll(sf::RenderWindow& window) const
{
    for (const auto& body : m_bodies)
    {
        body.Render(window);
    }
}

void BodyManager::SetCameraOffsetForAll(const sf::Vector2f& offset)
{
    for (auto& body : m_bodies)
    {
        body.SetCameraOffset(offset);
    }
}

void BodyManager::EnableTrailsForAll(bool enable)
{
    for (auto& body : m_bodies)
    {
        body.EnableTrail(enable);
    }
}

void BodyManager::ClearTrailsForAll()
{
    for (auto& body : m_bodies)
    {
        body.ClearTrail();
    }
}