#include "Game.h"

static const int PLAYER_HEIGHT = 100;
static const int PLAYER_WIDTH = 30;
static const float PLAYER_HEALTH = 100.0f;
static const float PLAYER_Y_VELOCITY = 300.0f;
static const float WAPON_X_VELOCITY = 800.0f;
static const float WAPON_DAMAGE = 10.0f;
static const int HEALTH_HEIGHT = 20;
static const SDL_Color PLAYER1_COLOR = { 0xFF,0x00,0x00,0xFF };
static const SDL_Color WAPON1_COLOR = { 0xFF,0xFF,0x00,0xFF };
static const SDL_Color PLAYER2_COLOR = { 0x00,0x00,0xFF,0xFF };
static const SDL_Color WAPON2_COLOR = { 0x00,0xFF,0xFF,0xFF };

SDL_Rect g_health1;
SDL_Rect g_health2;

static bool rect_collide(const SDL_Rect &rect1, const SDL_Rect &rect2)
{
    if (((rect1.x + rect1.w) > rect2.x) && (rect1.x < (rect2.x + rect2.w))) {
        if (((rect1.y + rect1.h) > rect2.y) && (rect1.y < (rect2.y + rect2.h))) {
            return true;
        }
    }
    return false;
}


Game::Game()
: m_is_running(true),
  m_window(nullptr),
  m_renderer(nullptr),
  m_ticks_count(0),
  m_screen_width(1600),
  m_screen_height(900)

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
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_screen_width,
                                m_screen_height,
                                SDL_WINDOW_SHOWN);
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

    InitGameObjects();

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

    // get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // if escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        m_is_running = false;
    }

    InputGameObjects(state);
}

void Game::UpdateGame()
{
    // wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + 16))
        ;

    // delta time is the difference in ticks from last frame
    // convert to seconds
    float delta_time = (SDL_GetTicks() - m_ticks_count) / 1000.0f;
    
    // Clamp maximum delta time value
    if (delta_time > 0.05f) {
        delta_time = 0.05f;
    }

    // Update ticks counts (for next frame)
    m_ticks_count = SDL_GetTicks();

    // update Game objects
    UpdateGameObjects(delta_time);
}

void Game::GenerateOutput()
{
    // Set black color
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);

    // Clear render
    SDL_RenderClear(m_renderer);

    // Draw Game Objects
    DrawGameObjects(m_renderer);

    // Swap front buffer and back buffer
    SDL_RenderPresent(m_renderer);
}

////////////////////////////////////////////////////////////////////////
void Game::InitGameObjects()
{
    /////////////////////////////////////////////////
    m_player1.w = PLAYER_WIDTH;
    m_player1.h = PLAYER_HEIGHT;
    m_player1.ydir = 0;
    m_player1.x = (m_screen_width / 3.0f - m_player1.w) / 2.0f;
    m_player1.y = (m_screen_height - m_player1.h) / 2.0f;
    m_player1.yv = PLAYER_Y_VELOCITY;
    m_player1.health = PLAYER_HEALTH;
    /////////////////////////////////////////////////
    m_wapon1.valid = false;
    m_wapon1.w = PLAYER_WIDTH;
    m_wapon1.h = PLAYER_HEIGHT / 10;
    m_wapon1.xdir = 1;
    m_wapon1.x = m_player1.x + m_player1.w;
    m_wapon1.y = m_player1.y + m_player1.h / 2.0f;
    m_wapon1.xv = WAPON_X_VELOCITY;
    m_wapon1.damage = WAPON_DAMAGE;
    /////////////////////////////////////////////////
    m_player2.w = PLAYER_WIDTH;
    m_player2.h = PLAYER_HEIGHT;
    m_player2.ydir = 0;
    m_player2.x = m_screen_width - ((m_screen_width / 3.0f - m_player2.w) / 2.0f) - m_player2.w;
    m_player2.y = (m_screen_height - m_player2.h) / 2.0f;
    m_player2.yv = PLAYER_Y_VELOCITY;
    m_player2.health = PLAYER_HEALTH;
    /////////////////////////////////////////////////
    m_wapon2.valid = false;
    m_wapon2.w = PLAYER_WIDTH;
    m_wapon2.h = PLAYER_HEIGHT / 10;
    m_wapon2.xdir = -1;
    m_wapon2.x = m_player2.x - m_wapon2.w;
    m_wapon2.y = m_player2.y + m_player2.h / 2.0f;
    m_wapon2.xv = WAPON_X_VELOCITY;
    m_wapon2.damage = WAPON_DAMAGE;

    //////////////////////////////////////////////////
    g_health1.w = (m_screen_width / 3.0f - 20);
    g_health1.h = HEALTH_HEIGHT;
    g_health1.x = (m_screen_width / 3.0f - g_health1.w) / 2.0f;
    g_health1.y = 20;
    //////////////////////////////////////////////////
    g_health2.w = (m_screen_width / 3.0f - 20);
    g_health2.h = HEALTH_HEIGHT;
    g_health2.x = m_screen_width - ((m_screen_width / 3.0f - g_health2.w) / 2.0f) - g_health2.w;
    g_health2.y = 20;
}

void Game::InputGameObjects(const Uint8* state)
{
    // update player1 direction based on W/S keys
    m_player1.ydir = 0;
    if (state[SDL_SCANCODE_W]) {
        m_player1.ydir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        m_player1.ydir += 1;
    }

    // update wapon1
    if (state[SDL_SCANCODE_SPACE] && !m_wapon1.valid) {
        m_wapon1.valid = true;
        m_wapon1.x = m_player1.x + m_player1.w;
        m_wapon1.y = m_player1.y + m_player1.h / 2.0f;
    }

    // update player2 direction based on UP/DOWN keys
    m_player2.ydir = 0;
    if (state[SDL_SCANCODE_UP]) {
        m_player2.ydir -= 1;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        m_player2.ydir += 1;
    }

    // update wapon2
    if (state[SDL_SCANCODE_KP_ENTER] && !m_wapon2.valid) {
        m_wapon2.valid = true;
        m_wapon2.x = m_player2.x - m_wapon2.w;
        m_wapon2.y = m_player2.y + m_player2.h / 2.0f;
    }

}

void Game::UpdateGameObjects(float delta_time)
{
    // update player1 position based on direction
    if (m_player1.ydir != 0) {
        m_player1.y += m_player1.ydir * m_player1.yv * delta_time;
        // make sure player doesn't move off screen
        if (m_player1.y < 0) {
            m_player1.y = 0;
        }
        else if (m_player1.y > (m_screen_height - m_player1.h)) {
            m_player1.y = (m_screen_height - m_player1.h);
        }
    }

    // update wapon1 position
    if (m_wapon1.valid) {
        m_wapon1.x += m_wapon1.xdir * m_wapon1.xv * delta_time;

        SDL_Rect wapon1_rect{ static_cast<int>(m_wapon1.x), static_cast<int>(m_wapon1.y), m_wapon1.w, m_wapon1.h };
        SDL_Rect player2_rect{ static_cast<int>(m_player2.x), static_cast<int>(m_player2.y), m_player2.w, m_player2.h };
        if (rect_collide(wapon1_rect, player2_rect)) {
            m_wapon1.valid = false;
            m_player2.health -= m_wapon1.damage;

            if (m_player2.health < 0) {
                m_player2.health = 0;
            }
        }

        if (m_wapon1.x > m_screen_width) {
            m_wapon1.valid = false;
        }
    }

    // update player2 position based on direction
    if (m_player2.ydir != 0) {
        m_player2.y += m_player2.ydir * m_player2.yv * delta_time;
        // make sure player doesn't move off screen
        if (m_player2.y < 0) {
            m_player2.y = 0;
        }
        else if (m_player2.y > (m_screen_height - m_player2.h)) {
            m_player2.y = (m_screen_height - m_player2.h);
        }
    }

    // update wapon2 position
    if (m_wapon2.valid) {
        m_wapon2.x += m_wapon2.xdir * m_wapon2.xv * delta_time;

        SDL_Rect wapon2_rect{ static_cast<int>(m_wapon2.x), static_cast<int>(m_wapon2.y), m_wapon2.w, m_wapon2.h };
        SDL_Rect player1_rect{ static_cast<int>(m_player1.x), static_cast<int>(m_player1.y), m_player1.w, m_player1.h };
        if (rect_collide(wapon2_rect, player1_rect)) {
            m_wapon2.valid = false;
            m_player1.health -= m_wapon2.damage;

            if (m_player1.health < 0) {
                m_player1.health = 0;
            }
        }

        if (m_wapon2.x < 0) {
            m_wapon2.valid = false;
        }
    }
}

void Game::DrawGameObjects(SDL_Renderer* renderer)
{
    // Draw player1
    SDL_SetRenderDrawColor(renderer, PLAYER1_COLOR.r, PLAYER1_COLOR.g, PLAYER1_COLOR.b, PLAYER1_COLOR.a);
    SDL_Rect player1_rect{ static_cast<int>(m_player1.x), static_cast<int>(m_player1.y), m_player1.w, m_player1.h };
    SDL_RenderFillRect(renderer, &player1_rect);

    // Draw Wapon1
    if (m_wapon1.valid) {
        SDL_SetRenderDrawColor(renderer, WAPON1_COLOR.r, WAPON1_COLOR.g, WAPON1_COLOR.b, WAPON1_COLOR.a);
        SDL_Rect wapon1_rect{ static_cast<int>(m_wapon1.x), static_cast<int>(m_wapon1.y), m_wapon1.w, m_wapon1.h };
        SDL_RenderFillRect(renderer, &wapon1_rect);
    }

    // Draw player2
    SDL_SetRenderDrawColor(renderer, PLAYER2_COLOR.r, PLAYER2_COLOR.g, PLAYER2_COLOR.b, PLAYER2_COLOR.a);
    SDL_Rect player2_rect{ static_cast<int>(m_player2.x), static_cast<int>(m_player2.y), m_player2.w, m_player2.h };
    SDL_RenderFillRect(renderer, &player2_rect);

    // Draw Wapon2
    if (m_wapon2.valid) {
        SDL_SetRenderDrawColor(renderer, WAPON2_COLOR.r, WAPON2_COLOR.g, WAPON2_COLOR.b, WAPON2_COLOR.a);
        SDL_Rect wapon2_rect{ static_cast<int>(m_wapon2.x), static_cast<int>(m_wapon2.y), m_wapon2.w, m_wapon2.h };
        SDL_RenderFillRect(renderer, &wapon2_rect);
    }


    // Draw Player1 health
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect health1_rect{ g_health1.x, g_health1.y, (m_player1.health / PLAYER_HEALTH)*g_health1.w, g_health1.h };
    SDL_RenderFillRect(renderer, &health1_rect);

    // Draw Player2 health
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect health2_rect{ g_health2.x, g_health2.y, (m_player2.health / PLAYER_HEALTH)*g_health2.w, g_health2.h };
    SDL_RenderFillRect(renderer, &health2_rect);
}
