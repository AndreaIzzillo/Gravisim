#pragma once

struct Settings
{
    static constexpr const char* WindowTitle = "Gravisim";

    static constexpr unsigned int WindowWidth = 1280;
    static constexpr unsigned int WindowHeight = 720;
    static constexpr unsigned int TargetFPS = 60;
    static constexpr unsigned int AntiAliasingLevel = 8;

    static constexpr float GravityConstant = 1500.f;
};