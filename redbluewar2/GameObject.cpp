#include "GameObject.h"
#include "Math.h"

GameObject::GameObject()
    :m_dead(false),
    m_pos{ 0,0 },
    m_rotation(0.0f),
    m_max_speed(0.0f),
    m_speed(0.0f),
    m_texture(nullptr),
    m_texture_width(0),
    m_texture_height(0)
{

}


GameObject::~GameObject()
{

}

void GameObject::SetDead(bool dead)
{
    m_dead = dead;
}
bool GameObject::GetDead() const
{
    return m_dead;
}
void GameObject::SetPosition(const Vector2& pos)
{
    m_pos = pos;
}
const Vector2& GameObject::GetPosition() const
{
    return m_pos;
}
void GameObject::SetRotation(float rotation)
{
    m_rotation = rotation;
}
float GameObject::GetRotation() const
{
    return m_rotation;
}
Vector2 GameObject::GetForward() const
{
    return Vector2(cosf(m_rotation), -sinf(m_rotation));
}
///////////////////////////////////////////////////////////////////////////////////
void GameObject::SetMaxSpeed(float max_speed)
{
    m_max_speed = max_speed;
}
float GameObject::GetMaxSpeed() const
{
    return m_max_speed;
}
void GameObject::SetSpeed(float speed)
{
    m_speed = speed;
}
float GameObject::GetSpeed() const
{
    return m_speed;
}
////////////////////////////////////////////////////////////////////////////////////
void GameObject::Update(float delta_time)
{
    if (!Math::NearZero(m_speed)) {
        Vector2 pos = m_pos;
        pos += GetForward() * m_speed * delta_time;
        m_pos = pos;
    }
}

////////////////////////////////////////////////////////////////////////////////////
void GameObject::GetSize(int &width, int &height)
{
    width = m_texture_width;
    height = m_texture_height;
}
void GameObject::SetTexture(SDL_Texture* texture)
{
    m_texture = texture;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_width, &m_texture_height);
    SDL_Log("width:%d, height:%d", m_texture_width, m_texture_height);
}
void GameObject::Draw(SDL_Renderer* renderer)
{
    if (m_dead)
        return;
    if (m_texture) {
        SDL_Rect rect;
        rect.w = m_texture_width;
        rect.h = m_texture_height;
        rect.x = static_cast<int>(m_pos.x - rect.w / 2);
        rect.y = static_cast<int>(m_pos.y - rect.h / 2);

        // draw
        SDL_RenderCopy(renderer,
            m_texture,
            nullptr,
            &rect);
    }
}