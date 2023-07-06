#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <optional>

class TextureManager
{
    public:
        TextureManager();
        ~TextureManager();
        bool load(const std::string& path, const std::string& name);
        std::optional<sf::Texture*> get(const std::string& name);
    private:
        std::unordered_map<std::string, sf::Texture> textures;
};

#endif