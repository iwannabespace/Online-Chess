#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>

class Piece : public sf::Drawable
{
    public:
        enum class Type
        {
            WPawn,
            WBishop,
            WKnight,
            WRook,
            WQueen,
            WKing,
            BPawn,
            BBishop,
            BKnight,
            BRook,
            BQueen,
            BKing,
        };
    public:
        Piece();
        Piece(sf::Texture* texture, Type type, sf::Vector2i index, sf::Vector2u winsize);
        ~Piece();
        void setIndex(sf::Vector2i index);
        void setPosition(sf::Vector2f position);
        sf::Vector2i getIndex() const;
        sf::Vector2f getPosition() const;
        sf::FloatRect getGlobalBounds() const;
        sf::FloatRect getLocalBounds() const;
    private:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
    private:
        Type type;
        sf::Sprite sprite;
        sf::Vector2u winsize;
        sf::Vector2i index;
};

#endif