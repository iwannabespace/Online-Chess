#include "../include/piece.hpp"
#include <iostream>

Piece::Piece()
{
}

Piece::Piece(sf::Texture* texture, Type type, sf::Vector2i index, sf::Vector2u winsize)
    : type(type), winsize(winsize), index(index)
{
    if (!texture)
        throw "texture is nullptr";

    sprite.setTexture(*texture);

    float swidth = winsize.x / 8;
    float sheight = winsize.y / 8;
    auto local = sprite.getLocalBounds();

    sprite.setScale({ 
        (swidth / local.width) / 1.35f,
        (sheight / local.height) / 1.35f,
    });

    sprite.setOrigin({ local.width / 2, local.height / 2});
}

Piece::~Piece()
{
}

void Piece::setIndex(sf::Vector2i index)
{
    this->index = index;
}

void Piece::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
}

sf::Vector2i Piece::getIndex() const
{
    return index;
}

sf::Vector2f Piece::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Piece::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

sf::FloatRect Piece::getLocalBounds() const
{
    return sprite.getLocalBounds();
}

void Piece::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    target.draw(sprite, states);
}