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
    void FixedUpdate(sf::Time deltaTime);
    void Render();

private:
    sf::RenderWindow m_window;
    sf::View m_view;
    sf::Clock m_clock;
    sf::Time m_accumulator;

    BodyManager m_bodyManager;

    float m_timeScale;
    bool m_trailsEnabled;
};