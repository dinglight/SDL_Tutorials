#pragma once

#include <SDL.h>

struct Player {
    float x;   // position
    float y;   // position
    int w;     // width
    int h;     // height
    int ydir;  // y direction, up: -1, down: 1
    float yv;  // y velocity
    float health;
};

struct Wapon {
    float x;
    float y;
    int w;
    int h;
    int xdir;    // x direction, left:-1, right:1
    float xv;   // x velocity
    bool valid;
    float damage;
};

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
    void InitGameObjects();
    void InputGameObjects(const Uint8* state);
    void UpdateGameObjects(float delta_time);
    void DrawGameObjects(SDL_Renderer* renderer);
private:
    bool m_is_running;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_ticks_count;
    int m_screen_width;
    int m_screen_height;

    // game object
    Player m_player1;
    Wapon m_wapon1;

    Player m_player2;
    Wapon m_wapon2;

};

