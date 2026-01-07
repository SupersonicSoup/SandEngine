#pragma once

#include <chrono>

class Time {
public:
    inline static float TimeScale = 1.0f;
    inline static bool Freeze = false;
    inline static float physicsTimeStep = 1.0f / 144.0f;
    inline static float maxDeltaTime = 0.2f;
    inline static float time = 0.0f;
    inline static double accumulator = 0.0f;

    static void Initialize();
    static void Update();
    static float Delta();
    static float DeltaTimeMS();
    static std::chrono::high_resolution_clock::time_point GetCurrentTime();
    static std::chrono::high_resolution_clock::time_point GetStartTime();

private:
    inline static std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
    inline static float previousDeltaTime;
    inline static float deltaTime;
};