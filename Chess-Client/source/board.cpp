#include "../include/board.hpp"
#include <iostream>

Board::Board(sf::RenderWindow& window, TextureManager& manager, Common::Side side)
    : window(window), manager(manager), side(side)
{
    std::string basePath = "images/";
    sf::Vector2u winsize = window.getSize();
    float swidth = winsize.x / 8;
    float sheight = winsize.y / 8;
    bool isWhiteSquare = true;
    bool isWhiteSide = (side == Common::Side::White);

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            squares[i][j].setSize({ swidth, sheight });
            squares[i][j].setPosition({ j * swidth, i * sheight });
            squares[i][j].setFillColor(isWhiteSquare ? Common::Color::WhiteSquare : Common::Color::BlackSquare);
            isWhiteSquare = !isWhiteSquare;
        }

        isWhiteSquare = !isWhiteSquare;
    }

    whites = {
        Piece(manager.get("WRook").value(),   Piece::Type::WRook,   { isWhiteSide ? 7 : 0, 0 }, winsize),
        Piece(manager.get("WKnight").value(), Piece::Type::WKnight, { isWhiteSide ? 7 : 0, 1 }, winsize),
        Piece(manager.get("WBishop").value(), Piece::Type::WBishop, { isWhiteSide ? 7 : 0, 2 }, winsize),
        Piece(manager.get("WQueen").value(),  Piece::Type::WQueen,  { isWhiteSide ? 7 : 0, 3 }, winsize),
        Piece(manager.get("WKing").value(),   Piece::Type::WKing,   { isWhiteSide ? 7 : 0, 4 }, winsize),
        Piece(manager.get("WBishop").value(), Piece::Type::WBishop, { isWhiteSide ? 7 : 0, 5 }, winsize),
        Piece(manager.get("WKnight").value(), Piece::Type::WKnight, { isWhiteSide ? 7 : 0, 6 }, winsize),
        Piece(manager.get("WRook").value(),   Piece::Type::WRook,   { isWhiteSide ? 7 : 0, 7 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 0 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 1 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 2 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 3 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 4 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 5 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 6 }, winsize),
        Piece(manager.get("WPawn").value(),   Piece::Type::WPawn,   { isWhiteSide ? 6 : 1, 7 }, winsize),
    };

    blacks = {
        Piece(manager.get("BRook").value(),   Piece::Type::BRook,   { isWhiteSide ? 0 : 7, 0 }, winsize),
        Piece(manager.get("BKnight").value(), Piece::Type::BKnight, { isWhiteSide ? 0 : 7, 1 }, winsize),
        Piece(manager.get("BBishop").value(), Piece::Type::BBishop, { isWhiteSide ? 0 : 7, 2 }, winsize),
        Piece(manager.get("BQueen").value(),  Piece::Type::BQueen,  { isWhiteSide ? 0 : 7, 3 }, winsize),
        Piece(manager.get("BKing").value(),   Piece::Type::BKing,   { isWhiteSide ? 0 : 7, 4 }, winsize),
        Piece(manager.get("BBishop").value(), Piece::Type::BBishop, { isWhiteSide ? 0 : 7, 5 }, winsize),
        Piece(manager.get("BKnight").value(), Piece::Type::BKnight, { isWhiteSide ? 0 : 7, 6 }, winsize),
        Piece(manager.get("BRook").value(),   Piece::Type::BRook,   { isWhiteSide ? 0 : 7, 7 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 0 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 1 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 2 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 3 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 4 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 5 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 6 }, winsize),
        Piece(manager.get("BPawn").value(),   Piece::Type::BPawn,   { isWhiteSide ? 1 : 6, 7 }, winsize),
    };

    setPiecePositions();
}

Board::~Board()
{
}

void Board::drag()
{
    if (selected)
        selected->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
}   

void Board::onClick(sf::Mouse::Button button)
{
    if (button == sf::Mouse::Button::Left)
    {
        auto squareResult = getSquareOfMouse();

        if (squareResult.has_value())
        {
            auto pair = squareResult.value();
            auto pieceResult = getPieceOnIndex(pair.second);

            if (pieceResult.has_value())
                selected = pieceResult.value();
        }
    }
}

void Board::onRelease(sf::Mouse::Button button)
{
    if (selected && button == sf::Mouse::Button::Left)
    {
        sf::Vector2u winsize = window.getSize();
        float swidth = winsize.x / 8;
        float sheight = winsize.y / 8;
        auto global = selected->getGlobalBounds();
        auto squareResult = getSquareOfMouse();

        if (squareResult.has_value())
        {
            auto pair = squareResult.value();

            selected->setIndex(pair.second);

            auto position = sf::Vector2f(
                selected->getIndex().y * sheight,
                selected->getIndex().x * swidth
            );

            selected->setPosition({
                position.x + swidth / 2,
                position.y + sheight / 2
            });
        }

        else
        {
            auto position = sf::Vector2f(
                selected->getIndex().y * sheight,
                selected->getIndex().x * swidth
            );

            selected->setPosition({
                position.x + swidth / 2,
                position.y + sheight / 2
            });
        }

        selected = nullptr;
    }
} 

void Board::setPiecePositions()
{
    sf::Vector2u winsize = window.getSize();
    float swidth = winsize.x / 8;
    float sheight = winsize.y / 8;

    for (Piece& piece : whites)
    {
        auto global = piece.getGlobalBounds();
        auto position = sf::Vector2f(
            piece.getIndex().y * sheight,
            piece.getIndex().x * swidth
        );

        piece.setPosition({
            position.x + swidth / 2,
            position.y + sheight / 2
        });
    }

    for (Piece& piece : blacks)
    {
        auto global = piece.getGlobalBounds();
        auto position = sf::Vector2f(
            piece.getIndex().y * sheight,
            piece.getIndex().x * swidth
        );

        piece.setPosition({
            position.x + swidth / 2,
            position.y + sheight / 2,
        });
    }
}

std::optional<std::pair<sf::RectangleShape, sf::Vector2i>> Board::getSquareOfMouse() const
{
    for (size_t i = 0; i < 8; i++)  
        for (size_t j = 0; j < 8; j++)
            if (squares[i][j].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                return std::make_pair(squares[i][j], sf::Vector2i{ (int)i, (int)j });

    return std::nullopt;
}

std::optional<Piece*> Board::getPieceOnIndex(sf::Vector2i index)
{
    for (Piece& piece : whites)
        if (piece.getIndex() == index)
            return &piece;

    for (Piece& piece : blacks)
        if (piece.getIndex() == index)
            return &piece;

    return std::nullopt;
}

void Board::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            target.draw(squares[i][j], states);

    for (const Piece& piece : whites)
        target.draw(piece, states);

    for (const Piece& piece : blacks)
        target.draw(piece, states);
}