#pragma once
#include "Game.h"

class GameObject;
class RBWar :
    public Game
{
public:
    RBWar();
    virtual ~RBWar();
    virtual bool OnInitialize() override;
    virtual void OnFinalize() override;
    virtual void OnInput(const Uint8* state);
    virtual void OnUpdate(float delta_time) override;
    virtual void OnRender(SDL_Renderer* renderer) override;
private:
    void ProcessKeyboardInput(const Uint8* state, GameObject* ship,
        int up_key, int down_key, int fire_key, GameObject* rocket);
    void UpdateShip(float delta_time, GameObject* ship);
    void UpdateRocket(float delta_time, GameObject* rocket, GameObject* ship);
private:
    GameObject* m_ship1;
    GameObject* m_ship2;
    GameObject* m_rocket1;
    GameObject* m_rocket2;
};

