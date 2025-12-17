#include "../core/core_settings.hpp"
#include "../core/simulation.hpp"
#include "../bodies/body.hpp"

std::unique_ptr<Simulation> SolarSystem()
{
    constexpr float w2 = static_cast<float>(Settings::WindowWidth) / 2.f;
    constexpr float h2 = static_cast<float>(Settings::WindowHeight) / 2.f;

    auto sim = std::make_unique<Simulation>();

    struct PlanetCfg
    {
        const char* name;
        float r;
        float mass;
        float radius;
        float speedFactor;
        sf::Color color;
        float theta;
    };

    const float G = Settings::GravityConstant;
    const float sunMass = 10000.f;

    Body sun({w2, h2}, sunMass, 24.f, sf::Color::Yellow);
    sim->AddBody(sun);

    std::array<PlanetCfg, 8> planets{{
        {"Mercury", 50.f, 0.0010f, 3.f, 1.02f, sf::Color(169, 169, 169), 0.1f},
        {"Venus",   80.f, 0.0015f, 3.5f, 1.00f, sf::Color(237, 201, 175), 1.7f},
        {"Earth",  115.f, 0.0020f, 4.5f, 1.00f, sf::Color(80, 120, 200), 3.0f},
        {"Mars",   150.f, 0.0012f, 4.0f, 0.98f, sf::Color(188, 39, 50), 2.4f},
        {"Jupiter",200.f, 0.0120f, 8.0f, 0.94f, sf::Color(210, 161, 109), 0.9f},
        {"Saturn", 245.f, 0.0100f, 7.0f, 0.92f, sf::Color(222, 206, 172), 2.6f},
        {"Uranus", 270.f, 0.0090f, 6.5f, 0.91f, sf::Color(175, 238, 238), 1.5f},
        {"Neptune",300.f, 0.0080f, 6.0f, 0.90f, sf::Color(70, 120, 200), 4.0f},
    }};

    for (const auto& p : planets)
    {
        sf::Vector2f pos{
            w2 + p.r * std::cos(p.theta),
            h2 + p.r * std::sin(p.theta)
        };
        Body b(pos, p.mass, p.radius, p.color);

        sf::Vector2f tangent{-std::sin(p.theta), std::cos(p.theta)};
        float v = std::sqrt(G * sunMass / p.r) * 1.0f;

        b.ApplyForce(tangent * v * p.mass, sf::seconds(1.f));

        sim->AddBody(b);
    }

    return sim;
}