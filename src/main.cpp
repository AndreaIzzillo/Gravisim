#include "core/core_settings.hpp"
#include "core/simulation.hpp"
#include "bodies/body.hpp"

std::unique_ptr<Simulation> ThreeBody()
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

std::unique_ptr<Simulation> RingOrbit()
{
    constexpr float w2 = static_cast<float>(Settings::WindowWidth) / 2.f;
    constexpr float h2 = static_cast<float>(Settings::WindowHeight) / 2.f;

    Body sun({w2, h2}, 2000.f, 30.f, sf::Color::Yellow);

    auto sim = std::make_unique<Simulation>();
    sim->AddBody(sun);

    const int count = 20;
    const float innerR = 120.f;
    const float outerR = 260.f;

    for (int i = 0; i < count; ++i)
    {
        float t = static_cast<float>(i) / count;
        float angle = t * 2.f * 3.14159265f;
        float r = innerR + (outerR - innerR) * (0.3f + 0.7f * (i % 2));
        sf::Vector2f pos{w2 + r * std::cos(angle), h2 + r * std::sin(angle)};

        float mass = 2.f;
        float radius = 4.f;
        Body b(pos, mass, radius, sf::Color(100, 200, 255));

        sf::Vector2f dir{-std::sin(angle), std::cos(angle)};
        float speed = std::sqrt(2500.f * 2000.f / r);
        b.ApplyForce(dir * speed * mass, sf::seconds(1.f));

        sim->AddBody(b);
    }

    return sim;
}

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


int main()
{
    SolarSystem()->Run();

    return 0;
}