#include "Game.h"
#include <iostream>
#include <SDL_image.h>

Game::Game()
:m_running(false),
 m_window_width(800),
 m_window_height(600),
 m_window(nullptr),
 m_renderer(nullptr),
 m_texture(nullptr),
 m_texture_width(0),
 m_texture_height(0),
 m_texture_x(0),
 m_texture_frame_count(0)
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
                                    m_window_width,
                                    m_window_height,
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

    LoadTexture("assets/tard.png");
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
    m_texture_x = m_texture_width * int((SDL_GetTicks()/100)%m_texture_frame_count);
}

void Game::Render()
{

    // clear the renderer to the draw color
    SDL_RenderClear(m_renderer);

    // render texture to screen
    DrawTexture(m_renderer);

    // draw the screen
    SDL_RenderPresent(m_renderer);
}

void Game::Clean()
{
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;

    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    // quit SDL subsystem
    SDL_Quit();
}

void Game::LoadTexture(const std::string & file_path)
{
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    if (surface == nullptr) {
        std::cout << IMG_GetError() << std::endl;
    } else {
        m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (m_texture == nullptr) {
            std::cout << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(surface);

        //SDL_QueryTexture(m_texture, nullptr, nullptr,
        //                 &m_texture_width, &m_texture_height);
        
        m_texture_width = m_texture_height = 24;
        m_texture_frame_count = 24;
        std::cout << "texture width:" << m_texture_width << ", height:" << m_texture_height << std::endl; 
    }
}

void Game::DrawTexture(SDL_Renderer* renderer)
{
    if (m_texture == nullptr) {
        return;
    }

    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = m_texture_x;
    srcRect.y = 0;
    srcRect.w = m_texture_width;
    srcRect.h = m_texture_height;
    
    destRect.w = 100;
    destRect.h = 100;
    destRect.x = int((m_window_width - destRect.w)/2);
    destRect.y = int((m_window_height - destRect.h)/2);

    SDL_RenderCopy(renderer, m_texture, &srcRect, &destRect);
}
