#include "../include/texture_manager.hpp"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::load(const std::string& path, const std::string& name)
{
    return textures[name].loadFromFile(path);
}

std::optional<sf::Texture*> TextureManager::get(const std::string& name)
{
    if (textures.count(name))
        return &textures[name];
    
    return std::nullopt;
}