#ifndef BOARD_HPP
#define BOARD_HPP

#include "texture_manager.hpp"
#include "piece.hpp"
#include "common.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <optional>

class Board : public sf::Drawable
{
    public:
        Board(sf::RenderWindow& window, TextureManager& manager, Common::Side side);
        ~Board();
        void drag();
        void onClick(sf::Mouse::Button button);
        void onRelease(sf::Mouse::Button button);
    private:
        void setPiecePositions();
        std::optional<std::pair<sf::RectangleShape, sf::Vector2i>> getSquareOfMouse() const; 
        std::optional<Piece*> getPieceOnIndex(sf::Vector2i index);
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
    private:
        std::array<std::array<sf::RectangleShape, 8>, 8> squares;
        std::array<Piece, 16> whites;
        std::array<Piece, 16> blacks;
        sf::RenderWindow& window;
        TextureManager& manager;
        Piece* selected = nullptr;
        Common::Side side;
};

#endif