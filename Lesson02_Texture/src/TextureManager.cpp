#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>

TextureManager& TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

bool TextureManager::Load(const std::string file_name,
                          const std::string id,
                          SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(file_name.c_str());
    if (surface == nullptr) {
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    m_texture_map.emplace(id, texture);
    return true;
}
void TextureManager::Clean()
{

}
