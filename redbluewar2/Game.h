#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Game
{
public:
    Game();
    virtual ~Game();
    void SetWinSize(int width, int height);
    void GetWinSize(int &width, int &height);
    void Run();
    SDL_Texture* GetTexture(const std::string & file_name);

protected:
    virtual bool OnInitialize();
    virtual void OnFinalize();
    virtual void OnInput(const Uint8* state);
    virtual void OnUpdate(float delta_time);
    virtual void OnRender(SDL_Renderer* renderer);
private:
    bool Initialize();
    void Finalize();
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void UnloadTextures();
private:
    bool m_running;
    Uint32 m_ticks_count;
    std::string m_win_title;
    int m_win_width;
    int m_win_height;
    uint32_t m_win_flag;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    std::unordered_map<std::string, SDL_Texture*> m_texture_map;
};

