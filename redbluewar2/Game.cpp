#include "Game.h"
#include <SDL_image.h>
#include "GameObject.h"
Game::Game()
    :m_running(true),
    m_ticks_count(0),
    m_win_title("Game"),
    m_win_width(1280),
    m_win_height(720),
    m_win_flag(SDL_WINDOW_SHOWN),
    m_window(nullptr),
    m_renderer(nullptr)
{
    SDL_Log("Game engine construct");
}
Game::~Game()
{
    SDL_Log("Game engine destruct");
}
void Game::SetWinSize(int width, int height)
{
    m_win_width = width;
    m_win_height = height;
}
void Game::GetWinSize(int &width, int &height)
{
    width = m_win_width;
    height = m_win_height;
}
void Game::Run()
{
    SDL_Log("Game Run");
    m_running = Initialize();
    while (m_running) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
    Finalize();
}
SDL_Texture* Game::GetTexture(const std::string & file_name)
{
    SDL_Texture* texture = nullptr;
    auto it = m_texture_map.find(file_name);
    if (it != m_texture_map.end()) {
        texture = it->second;
    }
    else {
        // load from file
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (!surface) {
            SDL_Log("Failed to load texture file %s", file_name.c_str());
            return nullptr;
        }

        // create texture from surface
        texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (!texture) {
            SDL_Log("Failed to create texture from surface %s", file_name.c_str());
            return nullptr;
        }
        m_texture_map.emplace(file_name, texture);
    }
    return texture;
}
//////////////////////////////////////////////////////////
bool Game::OnInitialize()
{
    return true;
}
void Game::OnFinalize()
{

}
void Game::OnInput(const Uint8* state)
{

}
void Game::OnUpdate(float delta_time)
{

}
void Game::OnRender(SDL_Renderer* renderer)
{

}
//////////////////////////////////////////////////////////
bool Game::Initialize()
{
    SDL_Log("Game Initialize");
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize:%s", SDL_GetError());
        return false;
    }
    // create window
    m_window = SDL_CreateWindow(m_win_title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_win_width,
        m_win_height,
        m_win_flag);
    if (nullptr == m_window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    // create renderer
    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (nullptr == m_renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    // initialize sdl image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    
    return OnInitialize();
}

void Game::Finalize()
{
    OnFinalize();
    // TODO
    UnloadTextures();

    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    SDL_Log("Game Finalize");
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_running = false;
            break;
        }
    }

    // get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    OnInput(state);
}
void Game::UpdateGame()
{
    // wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + 16))
        ;

    // calculate the delta time from last frame
    float delta_time = (SDL_GetTicks() - m_ticks_count) / 1000.0f;

    // clamp maximum delta time value
    if (delta_time > 0.05f) {
        delta_time = 0.05f;
    }
    // update 
    OnUpdate(delta_time);

    m_ticks_count = SDL_GetTicks();
}
void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Draw all sprite components
    OnRender(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void Game::UnloadTextures()
{
    for (auto it : m_texture_map) {
        SDL_DestroyTexture(it.second);
    }
    m_texture_map.clear();
}