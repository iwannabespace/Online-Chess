#ifndef CHESS_HPP
#define CHESS_HPP

#include "texture_manager.hpp"
#include "board.hpp"
#include "piece.hpp"
#include "common.hpp"
#include <SFML/Graphics.hpp>
#include <array>

class Chess : public sf::Drawable
{
    public:
        Chess(sf::RenderWindow& window, TextureManager& manager, Common::Side side);
        ~Chess();
        Board& getBoard();
    private:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
    private:
        Board board;
        sf::Vector2u winsize;
        sf::RenderWindow& window;
};

#endif