#include "simulation.hpp"

#include "core_settings.hpp"

Simulation::Simulation()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = Settings::AntiAliasingLevel;

    m_window = sf::RenderWindow(
        sf::VideoMode(sf::Vector2u(Settings::WindowWidth, Settings::WindowHeight)),
        Settings::WindowTitle,
        sf::Style::Default,
        sf::State::Windowed,
        settings);

    m_clock = sf::Clock();
    m_accumulator = sf::Time::Zero;
    m_timeScale = 1.f;

    m_window.setFramerateLimit(Settings::TargetFPS);

    m_cameraOffset = sf::Vector2f(0.f, 0.f);

    m_trailsEnabled = true;
}

void Simulation::AddBody(const Body& body)
{
    m_bodyManager.AddBody(body);
}

void Simulation::Run()
{
    const sf::Time fixedDt = sf::seconds(1.f / 120.f);

    while (m_window.isOpen())
    {
        ProcessEvents();

        auto frameTime = m_clock.restart();
        frameTime *= m_timeScale;
        m_accumulator += frameTime;

        while (m_accumulator >= fixedDt)
        {
            Update(fixedDt);
            m_accumulator -= fixedDt;
        }

        Render();
    }
}

void Simulation::ProcessEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }

        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyEvent->scancode == sf::Keyboard::Scancode::U)
            {
                m_timeScale += 0.1f;
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::D)
            {
                m_timeScale = std::max(0.f, m_timeScale - 0.1f);
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::R)
            {
                m_timeScale = 1.f;
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::P)
            {
                m_trailsEnabled = !m_trailsEnabled;
                m_bodyManager.ClearTrailsForAll();
                m_bodyManager.EnableTrailsForAll(m_trailsEnabled);
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::Space)
            {
                m_timeScale = (m_timeScale == 0.f) ? 1.f : 0.f;
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::Right)
            {
                m_cameraOffset.x -= 20.f;
                m_bodyManager.ClearTrailsForAll();
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::Left)
            {
                m_cameraOffset.x += 20.f;
                m_bodyManager.ClearTrailsForAll();
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::Down)
            {
                m_cameraOffset.y -= 20.f;
                m_bodyManager.ClearTrailsForAll();
            }
            else if (keyEvent->scancode == sf::Keyboard::Scancode::Up)
            {
                m_cameraOffset.y += 20.f;
                m_bodyManager.ClearTrailsForAll();
            }
        }
    }
}

void Simulation::Update(sf::Time deltaTime)
{
    m_bodyManager.SetCameraOffsetForAll(m_cameraOffset);
    m_bodyManager.UpdateAll(deltaTime);
}

void Simulation::Render()
{
    m_window.clear(sf::Color::Black);
    m_bodyManager.RenderAll(m_window);
    m_window.display();
}