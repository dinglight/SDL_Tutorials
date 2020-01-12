#pragma once

#include <SDL.h>

class Game
{
public:
    Game();
    ~Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
private:
    bool m_is_running;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

