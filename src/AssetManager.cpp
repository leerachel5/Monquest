#include "AssetManager.hpp"
#include "Components.hpp"

AssetManager::AssetManager(Manager* mngr)
    : manager(mngr)
{}

AssetManager::~AssetManager(){
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id) {
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(id, false);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char *path) {
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
    TTF_Font* f = TTF_OpenFont(path.c_str(), fontSize);
    if (f == NULL) {
        std::cout << "Could not load font at path \"" << path << "\"" << std::endl;
        exit(1);
    }
    fonts.emplace(id, f);
}

TTF_Font* AssetManager::GetFont(std::string id) {
    return fonts[id];
}
