#include "../include/chess.hpp"

Chess::Chess(sf::RenderWindow& window, TextureManager& manager, Common::Side side)
    : board(window, manager, side), window(window)
{
}

Chess::~Chess()
{
}

Board& Chess::getBoard()
{
    return board;
}

void Chess::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    target.draw(board, states);
}