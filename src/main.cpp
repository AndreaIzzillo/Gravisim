#include "core/core_settings.hpp"
#include "core/simulation.hpp"
#include "bodies/body.hpp"

std::unique_ptr<Simulation> ThreeBodySimulation()
{
    constexpr float width_half = static_cast<float>(Settings::WindowWidth) / 2.f;
    constexpr float height_half = static_cast<float>(Settings::WindowHeight) / 2.f;

    sf::Vector2f b1_position{width_half - 100.f, height_half};
    sf::Vector2f b2_position{width_half + 100.f, height_half};
    sf::Vector2f b3_position{width_half, height_half + 200.f};

    float mass = 120.f;
    float radius = 5.f;

    Body b1(b1_position, mass, radius, sf::Color::Red);
    Body b2(b2_position, mass, radius, sf::Color::Green);
    Body b3(b3_position, mass, radius, sf::Color::Blue);

    b1.ApplyForce(sf::Vector2f(0.f, -4000.f), sf::seconds(1.f));
    b2.ApplyForce(sf::Vector2f(-4000.f, 1000.f), sf::seconds(1.f));
    b3.ApplyForce(sf::Vector2f(2000.f, 2000.f), sf::seconds(1.f));

    auto sim = std::make_unique<Simulation>();

    sim->AddBody(b1);
    sim->AddBody(b2);
    sim->AddBody(b3);

    return sim;
}

std::unique_ptr<Simulation> Orbit()
{
    constexpr float width_half = static_cast<float>(Settings::WindowWidth) / 2.f;
    constexpr float height_half = static_cast<float>(Settings::WindowHeight) / 2.f;

    sf::Vector2f big_position{width_half, height_half};
    sf::Vector2f small_position{width_half + 100.f, height_half};
    sf::Vector2f very_small_position{width_half + 110.f, height_half};

    Body big(big_position, 1000.f, 30.f, sf::Color::Magenta);
    Body small(small_position, 5.f, 5.f, sf::Color::Cyan);
    Body very_small(very_small_position, .1f, 2.f, sf::Color::Red);

    small.ApplyForce(sf::Vector2f(0.f, -800.f), sf::seconds(1.f));
    very_small.ApplyForce(sf::Vector2f(0.f, -12.f), sf::seconds(1.f));

    auto sim = std::make_unique<Simulation>();

    sim->AddBody(big);
    sim->AddBody(small);
    sim->AddBody(very_small);

    return sim;
}

int main()
{
    Orbit()->Run();

    return 0;
}