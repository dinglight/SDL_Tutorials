#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <string>
#include <unordered_map>
#include <SDL.h>

class TextureManager {
public:
    static TextureManager & GetInstance();
    ~TextureManager();
    bool Load(const std::string file_name,
              const std::string id,
              SDL_Renderer* renderer);
    void Clean();
private:
    TextureManager();
    TextureManager(const TextureManager& mgr);
    TextureManager& operator=(const TextureManager& mgr);
private:
    std::unordered_map<std::string, SDL_Texture*> m_texture_map;
};
#endif // __TEXTURE_MANAGER_H__
