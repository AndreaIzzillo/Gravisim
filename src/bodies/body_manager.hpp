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

private:
    std::vector<Body> m_bodies;
};