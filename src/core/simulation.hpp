#pragma once

#include "../bodies/body.hpp"
#include "../bodies/body_manager.hpp"

#include <SFML/Graphics.hpp>

class Simulation
{
public:
    Simulation();
    ~Simulation() = default;

    void AddBody(const Body& body);

    void Run();

private:
    void ProcessEvents();
    void Update(sf::Time deltaTime);
    void Render();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Time m_accumulator;
    float m_timeScale;

    BodyManager m_bodyManager;
};