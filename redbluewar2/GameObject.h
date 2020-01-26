#pragma once
#include <SDL.h>
#include "Vector2.h"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    void SetDead(bool dead);
    bool GetDead() const;

    void SetPosition(const Vector2 &pos);
    const Vector2& GetPosition() const;

    void SetRotation(float rotation);
    float GetRotation() const;

    Vector2 GetForward() const;

    void SetMaxSpeed(float max_speed);
    float GetMaxSpeed() const;
    void SetSpeed(float speed);
    float GetSpeed() const;
public:
    void Update(float delta_time);
public:
    void SetTexture(SDL_Texture* texture);
    void GetSize(int &width, int &height);
    void Draw(SDL_Renderer* renderer);
private:
    bool m_dead;
    Vector2 m_pos;
    float m_rotation;

    float m_max_speed;
    float m_speed;

    // draw component
    SDL_Texture* m_texture;
    int m_texture_width;
    int m_texture_height;
};

