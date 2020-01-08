#include "Game.h"
#include <iostream>

Game::Game()
:m_running(false),
 m_window(nullptr),
 m_renderer(nullptr)
{

}
Game::~Game()
{

}

bool Game::IsRunning() const
{
    return m_running;
}

bool Game::Init()
{
    bool success = false;
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL could not initialize, SDL Error:" << SDL_GetError() << std::endl;
        success = false;
    } else {
        // init the window
        m_window = SDL_CreateWindow("Game",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    800,
                                    600,
                                    SDL_WINDOW_SHOWN);
        if (nullptr == m_window) {
            std::cout << "Window could not be created, SDL Error:" << SDL_GetError() << std::endl;
            success = false;
        } else {
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (nullptr == m_renderer) {
                std::cout << "Renderer could not be created, SDL Error:" << SDL_GetError() << std::endl;
                success = false;
            } else {
                // set the draw color to black
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
                success = true;
                // start the main loop
                m_running = true;
            }
        }
    }
    return success;
}

void Game::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_running = false;
            break;
        default:
            break;
        }
    }
}

void Game::Update()
{

}

void Game::Render()
{
    // clear the renderer to the draw color
    SDL_RenderClear(m_renderer);
    // draw the screen
    SDL_RenderPresent(m_renderer);
}

void Game::Clean()
{
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    // quit SDL subsystem
    SDL_Quit();
}


