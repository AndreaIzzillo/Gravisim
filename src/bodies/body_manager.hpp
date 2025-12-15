#pragma once

#include <SFML/Graphics.hpp>

#include "body.hpp"

class BodyManager
{
public:
    BodyManager() = default;
    ~BodyManager() = default;

    void AddBody(const Body& body);
    void UpdateAll(sf::Time deltaTime);
    void RenderAll(sf::RenderWindow& window) const;

    void SetCameraOffsetForAll(const sf::Vector2f& offset);
    void EnableTrailsForAll(bool enable);
    void ClearTrailsForAll();

private:
    std::vector<Body> m_bodies;
};