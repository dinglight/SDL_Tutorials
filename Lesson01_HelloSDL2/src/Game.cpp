#include "Game.h"

Game::Game()
: m_is_running(true),
  m_window(nullptr),
  m_renderer(nullptr)
{
}


Game::~Game()
{

}

bool Game::Initialize()
{
    int sdl_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_result != 0) {
        SDL_Log("%s", SDL_GetError());
        return false;
    }
    m_window = SDL_CreateWindow("Game",
        100, 100, 1024, 768, 0);
    if (m_window == nullptr) {
        SDL_Log("%s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        SDL_Log("%s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::RunLoop()
{
    while (m_is_running) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
///////////////////////////////////////////////////////////////////////
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_is_running = false;
            break;
        }
    }
}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{
    // Set black color
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);

    // Clear render
    SDL_RenderClear(m_renderer);

    // Swap front buffer and back buffer
    SDL_RenderPresent(m_renderer);
}
