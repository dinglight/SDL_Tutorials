#pragma once
#include <string>
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
    void LoadTexture(const std::string &file_path);
    void DrawTexture(SDL_Renderer* renderer);
private:
    bool m_running;
    int m_window_width;
    int m_window_height;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    int m_texture_width;
    int m_texture_height;
    int m_texture_x;
    int m_texture_frame_count;
};

