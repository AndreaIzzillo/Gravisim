#include "core/core_settings.hpp"
#include "core/simulation.hpp"
#include "bodies/body.hpp"

#include <array>
#include <random>
#include <cmath>

std::unique_ptr<Simulation> CircumbinaryTrojans()
{
    constexpr float w2 = static_cast<float>(Settings::WindowWidth)  / 2.f;
    constexpr float h2 = static_cast<float>(Settings::WindowHeight) / 2.f;

    const float G = Settings::GravityConstant;

    auto sim = std::make_unique<Simulation>();

    auto setVelocity = [](Body& b, const sf::Vector2f& v)
    {
        b.ApplyForce(v * b.GetMass(), sf::seconds(1.f));
    };

    const float m1 = 8000.f;
    const float m2 = 5000.f;

    const float separation = 160.f;
    const float totalM = m1 + m2;

    const float r1 = separation * (m2 / totalM);
    const float r2 = separation * (m1 / totalM);

    const sf::Vector2f C{w2, h2};

    Body star1({C.x - r1, C.y}, m1, 16.f, sf::Color(255, 220, 120));
    Body star2({C.x + r2, C.y}, m2, 12.f, sf::Color(180, 220, 255));

    const float omega = std::sqrt(G * totalM / (separation * separation * separation));

    const float v1 = omega * r1;
    const float v2 = omega * r2;

    setVelocity(star1, {0.f, +v1});
    setVelocity(star2, {0.f, -v2});

    sim->AddBody(star1);
    sim->AddBody(star2);

    const float planetR = 340.f;
    const float planetM = 0.08f;
    const float planetRad = 6.f;

    const float planetTheta = 0.35f;
    sf::Vector2f planetPos{
        C.x + planetR * std::cos(planetTheta),
        C.y + planetR * std::sin(planetTheta)
    };

    Body planet(planetPos, planetM, planetRad, sf::Color(120, 200, 255));

    const float vPlanet = std::sqrt(G * totalM / planetR);
    sf::Vector2f tPlanet{-std::sin(planetTheta), std::cos(planetTheta)};
    setVelocity(planet, tPlanet * vPlanet);

    sim->AddBody(planet);

    auto addTrojan = [&](float thetaOffset, const sf::Color& col)
    {
        const float t = planetTheta + thetaOffset;
        sf::Vector2f pos{C.x + planetR * std::cos(t), C.y + planetR * std::sin(t)};
        Body trojan(pos, planetM * 0.12f, 4.f, col);

        sf::Vector2f tangent{-std::sin(t), std::cos(t)};
        setVelocity(trojan, tangent * vPlanet);

        sim->AddBody(trojan);
    };

    constexpr float deg60 = 3.1415926535f / 3.f;
    addTrojan(+deg60, sf::Color(255, 160, 80));
    addTrojan(-deg60, sf::Color(255, 120, 180));

    std::mt19937 rng(1337);
    std::uniform_real_distribution<float> distTheta(0.f, 2.f * 3.1415926535f);
    std::uniform_real_distribution<float> distR(220.f, 520.f);
    std::normal_distribution<float> distSpeedNoise(0.f, 0.045f);

    const int N = 30;
    for (int i = 0; i < N; ++i)
    {
        float r = distR(rng);
        float t = distTheta(rng);

        sf::Vector2f pos{C.x + r * std::cos(t), C.y + r * std::sin(t)};

        float m = 0.002f + 0.0015f * (i % 5);
        float rad = 2.f + 0.6f * (i % 4);

        Body a(pos, m, rad, sf::Color(200, 200, 200));

        float v = std::sqrt(G * totalM / r);
        v *= (1.f + distSpeedNoise(rng));

        sf::Vector2f tangent{-std::sin(t), std::cos(t)};
        setVelocity(a, tangent * v);

        sim->AddBody(a);
    }

    return sim;
}
