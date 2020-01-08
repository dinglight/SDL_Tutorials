#pragma once

#include <SDL.h>

class Game
{
public:
    Game();
    ~Game();

    bool IsRunning() const;

    bool Init();
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
private:
    bool m_running;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

