#ifndef COMMON_HPP
#define COMMON_HPP

#include <SFML/Graphics/Color.hpp>

namespace Common
{
    namespace Color
    {
        const sf::Color WhiteSquare = sf::Color(240, 217, 181);
        const sf::Color BlackSquare = sf::Color(181, 136, 99);
    }

    enum class Side
    {
        White,
        Black
    };
};

#endif