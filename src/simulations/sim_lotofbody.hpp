#include "../core/core_settings.hpp"
#include "../core/simulation.hpp"
#include "../bodies/body.hpp"

std::unique_ptr<Simulation> LotOfBody()
{

    constexpr float width_half = static_cast<float>(Settings::WindowWidth) / 2.f;
    constexpr float height_half = static_cast<float>(Settings::WindowHeight) / 2.f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> pos_offset(-120.f, 120.f);
    std::uniform_real_distribution<float> force_offset(-10000.f, 10000.f);

    sf::Vector2f b1_position{width_half - 100.f + pos_offset(gen), height_half + pos_offset(gen)};
    sf::Vector2f b2_position{width_half + 100.f + pos_offset(gen), height_half + pos_offset(gen)};
    sf::Vector2f b3_position{width_half + pos_offset(gen), height_half + 200.f + pos_offset(gen)};
    sf::Vector2f b4_position{width_half + pos_offset(gen), height_half - 200.f + pos_offset(gen)};
    sf::Vector2f b5_position{width_half - 200.f + pos_offset(gen), height_half - 100.f + pos_offset(gen)};
    sf::Vector2f b6_position{width_half + 200.f + pos_offset(gen), height_half + 100.f + pos_offset(gen)};
    sf::Vector2f b7_position{width_half - 150.f + pos_offset(gen), height_half + 150.f + pos_offset(gen)};
    sf::Vector2f b8_position{width_half + 150.f + pos_offset(gen), height_half - 150.f + pos_offset(gen)};

    float mass = 400.f;
    float radius = 5.f;

    Body b1(b1_position, mass, radius, sf::Color::Red);
    Body b2(b2_position, mass, radius, sf::Color::Green);
    Body b3(b3_position, mass, radius, sf::Color::Blue);
    Body b4(b4_position, mass, radius, sf::Color::Yellow);
    Body b5(b5_position, mass, radius, sf::Color::Cyan);
    Body b6(b6_position, mass, radius, sf::Color::Magenta);
    Body b7(b7_position, mass, radius, sf::Color::White);
    Body b8(b8_position, mass, radius, sf::Color(255, 165, 0));

    b1.ApplyForce(sf::Vector2f(0.f + force_offset(gen), -4000.f + force_offset(gen)), sf::seconds(1.f));
    b2.ApplyForce(sf::Vector2f(-4000.f + force_offset(gen), 1000.f + force_offset(gen)), sf::seconds(1.f));
    b3.ApplyForce(sf::Vector2f(2000.f + force_offset(gen), 2000.f + force_offset(gen)), sf::seconds(1.f));
    b4.ApplyForce(sf::Vector2f(3000.f + force_offset(gen), -1500.f + force_offset(gen)), sf::seconds(1.f));
    b5.ApplyForce(sf::Vector2f(-2500.f + force_offset(gen), 2000.f + force_offset(gen)), sf::seconds(1.f));
    b6.ApplyForce(sf::Vector2f(1500.f + force_offset(gen), -3000.f + force_offset(gen)), sf::seconds(1.f));
    b7.ApplyForce(sf::Vector2f(-2000.f + force_offset(gen), -2000.f + force_offset(gen)), sf::seconds(1.f));
    b8.ApplyForce(sf::Vector2f(0.f + force_offset(gen), 4000.f + force_offset(gen)), sf::seconds(1.f));

    auto sim = std::make_unique<Simulation>();

    sim->AddBody(b1);
    sim->AddBody(b2);
    sim->AddBody(b3);
    sim->AddBody(b4);
    sim->AddBody(b5);
    sim->AddBody(b6);
    sim->AddBody(b7);
    sim->AddBody(b8);

    return sim;
}
