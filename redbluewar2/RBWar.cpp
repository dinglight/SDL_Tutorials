#include "RBWar.h"
#include <iostream>
#include "GameObject.h"
#include "Math.h"
RBWar::RBWar()
    :m_ship1(nullptr)
{
    std::cout << "RBWar Construct" << std::endl;
}

RBWar::~RBWar()
{
    std::cout << "RBWar Destruct" << std::endl;
}

bool RBWar::OnInitialize()
{
    std::cout << "RBWar OnInitialize" << std::endl;
    m_ship1 = new GameObject();
    m_ship1->SetTexture(GetTexture("assets/ship1.png"));
    m_ship1->SetPosition({ 100.0f, 100.0f });
    m_ship1->SetMaxSpeed(300.0f);
    m_ship1->SetRotation(Math::PI / 2);

    m_ship2 = new GameObject();
    m_ship2->SetTexture(GetTexture("assets/ship2.png"));
    m_ship2->SetPosition({ 1100.0f, 100.0f });
    m_ship2->SetMaxSpeed(300.0f);
    m_ship2->SetRotation(Math::PI / 2);

    m_rocket1 = new GameObject();
    m_rocket1->SetDead(true);
    m_rocket1->SetTexture(GetTexture("assets/rocket1.png"));
    m_rocket1->SetMaxSpeed(800.0f);
    m_rocket1->SetRotation(0.0f);

    m_rocket2 = new GameObject();
    m_rocket2->SetDead(true);
    m_rocket2->SetTexture(GetTexture("assets/rocket2.png"));
    m_rocket2->SetMaxSpeed(800.0f);
    m_rocket2->SetRotation(Math::PI);

    return true;
}

void RBWar::OnFinalize()
{
    delete m_rocket2;
    m_rocket2 = nullptr;

    delete m_rocket1;
    m_rocket1 = nullptr;

    delete m_ship2;
    m_ship2 = nullptr;

    delete m_ship1;
    m_ship1 = nullptr;

    std::cout << "RBWar OnFinalize" << std::endl;
}
void RBWar::OnInput(const Uint8* state)
{
    ProcessKeyboardInput(state, m_ship1, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_SPACE, m_rocket1);
    ProcessKeyboardInput(state, m_ship2, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_KP_ENTER, m_rocket2);
}
void RBWar::OnUpdate(float delta_time)
{
    UpdateShip(delta_time, m_ship1);
    UpdateShip(delta_time, m_ship2);
    UpdateRocket(delta_time, m_rocket1, m_ship2);
    UpdateRocket(delta_time, m_rocket2, m_ship1);
}
void RBWar::OnRender(SDL_Renderer* renderer)
{
    m_ship1->Draw(renderer);
    m_ship2->Draw(renderer);
    m_rocket1->Draw(renderer);
    m_rocket2->Draw(renderer);
}

////////////////////////////////////////////////////////////
void RBWar::ProcessKeyboardInput(const Uint8* state, GameObject* ship,
    int up_key, int down_key, int fire_key, GameObject* rocket)
{
    float speed = 0.0f;
    if (state[up_key]) {
        speed += ship->GetMaxSpeed();
    }
    if (state[down_key]) {
        speed -= ship->GetMaxSpeed();
    }
    ship->SetSpeed(speed);

    if (state[fire_key]) {
        if (rocket->GetDead()) {
            rocket->SetDead(false);
            rocket->SetPosition(ship->GetPosition());
            rocket->SetSpeed(rocket->GetMaxSpeed());
        }
    }
}

void RBWar::UpdateShip(float delta_time, GameObject* ship)
{
    float speed = ship->GetSpeed();
    if (!Math::NearZero(speed)) {
        Vector2 pos = ship->GetPosition();
        pos += ship->GetForward() * speed * delta_time;
        ship->SetPosition(pos);
    }

    SDL_Rect win_rect;
    win_rect.x = win_rect.y = 0;
    GetWinSize(win_rect.w, win_rect.h);

    Vector2 ship_pos = ship->GetPosition();
    SDL_Rect ship_rect;
    ship->GetSize(ship_rect.w, ship_rect.h);
    ship_rect.x = static_cast<int>(ship_pos.x) - ship_rect.w / 2;
    ship_rect.y = static_cast<int>(ship_pos.y) - ship_rect.h / 2;

    bool flag = false;
    if (ship_rect.x < win_rect.x) {
        flag = true;
        ship_rect.x = win_rect.x;
    }
    if (ship_rect.y < win_rect.y) {
        flag = true;
        ship_rect.y = win_rect.y;
    }
    if (ship_rect.x > (win_rect.w - ship_rect.w)) {
        flag = true;
        ship_rect.x = (win_rect.w - ship_rect.w);
    }
    if (ship_rect.y > (win_rect.h - ship_rect.h)) {
        flag = true;
        ship_rect.y = (win_rect.h - ship_rect.h);
    }

    if (flag) {
        Vector2 pos;
        pos.x = float(ship_rect.x + ship_rect.w / 2);
        pos.y = float(ship_rect.y + ship_rect.h / 2);
        ship->SetPosition(pos);
    }
}

void RBWar::UpdateRocket(float delta_time, GameObject* rocket, GameObject* ship)
{
    if (rocket->GetDead()) {
        return;
    }

    float speed = rocket->GetSpeed();
    if (!Math::NearZero(speed)) {
        Vector2 pos = rocket->GetPosition();
        pos += rocket->GetForward() * speed * delta_time;
        rocket->SetPosition(pos);
    }

    Vector2 ship_pos = ship->GetPosition();
    SDL_Rect ship_rect;
    ship->GetSize(ship_rect.w, ship_rect.h);
    ship_rect.x = static_cast<int>(ship_pos.x) - ship_rect.w / 2;
    ship_rect.y = static_cast<int>(ship_pos.y) - ship_rect.h / 2;

    SDL_Rect win_rect;
    win_rect.x = win_rect.y = 0;
    GetWinSize(win_rect.w, win_rect.h);

    Vector2 rocket_pos = rocket->GetPosition();
    SDL_Rect rocket_rect;
    rocket->GetSize(rocket_rect.w, rocket_rect.h);
    rocket_rect.x = static_cast<int>(rocket_pos.x) - rocket_rect.w / 2;
    rocket_rect.y = static_cast<int>(rocket_pos.y) - rocket_rect.h / 2;
    if (!SDL_HasIntersection(&rocket_rect, &win_rect)) {
        rocket->SetDead(true);
    }

    if (SDL_HasIntersection(&rocket_rect, &ship_rect)) {
        rocket->SetDead(true);
        ship->SetDead(true);
    }
}