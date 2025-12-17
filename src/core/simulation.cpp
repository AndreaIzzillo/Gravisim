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

    m_view.setSize(sf::Vector2f(static_cast<float>(Settings::WindowWidth), static_cast<float>(Settings::WindowHeight)));
    m_view.setCenter(sf::Vector2f(static_cast<float>(Settings::WindowWidth) / 2.f, static_cast<float>(Settings::WindowHeight) / 2.f));
    m_window.setView(m_view);

    m_clock = sf::Clock();
    m_accumulator = sf::Time::Zero;
    m_timeScale = 1.f;

    m_window.setFramerateLimit(Settings::TargetFPS);

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

        Update(frameTime);

        frameTime *= m_timeScale;
        m_accumulator += frameTime;

        while (m_accumulator >= fixedDt)
        {
            FixedUpdate(fixedDt);
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

        if (const auto *keyEvent = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyEvent->scancode == sf::Keyboard::Scancode::U)
            {
                m_timeScale += 0.1f;
            }
            if (keyEvent->scancode == sf::Keyboard::Scancode::D)
            {
                m_timeScale = std::max(0.f, m_timeScale - 0.1f);
            }
            if (keyEvent->scancode == sf::Keyboard::Scancode::R)
            {
                m_timeScale = 1.f;
            }
            if (keyEvent->scancode == sf::Keyboard::Scancode::P)
            {
                m_trailsEnabled = !m_trailsEnabled;
                m_bodyManager.ClearTrailsForAll();
                m_bodyManager.EnableTrailsForAll(m_trailsEnabled);
            }
            if (keyEvent->scancode == sf::Keyboard::Scancode::Space)
            {
                m_timeScale = (m_timeScale == 0.f) ? 1.f : 0.f;
            }
        }
    }
}

void Simulation::Update(sf::Time deltaTime)
{
    float speed = 50.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
        speed = 200.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl))
        speed = 10.f;

    sf::Vector2f cameraDelta(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
        cameraDelta.x += 10.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
        cameraDelta.x -= 10.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
        cameraDelta.y += 10.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
        cameraDelta.y -= 10.f;

    cameraDelta *= deltaTime.asSeconds() * speed;

    m_view.move(cameraDelta);
    m_window.setView(m_view);
}

void Simulation::FixedUpdate(sf::Time deltaTime)
{
    m_bodyManager.UpdateAll(deltaTime);
}

void Simulation::Render()
{
    m_window.clear(sf::Color::Black);
    m_bodyManager.RenderAll(m_window);
    m_window.display();
}