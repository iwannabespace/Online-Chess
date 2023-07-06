#include <SFML/Graphics.hpp>
#include "include/chess.hpp"
#include "include/piece.hpp"
#include "include/texture_manager.hpp"
#include "include/client.hpp"
#include <iostream>
#include <thread>

int main()
{
    Client client("127.0.0.1", 3000);

    if (client.connect())
    {   
        std::cout << "Connected!" << std::endl;

        while (client.connected())
        {
            client.send("test");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        std::cout << "Server is down!" << std::endl;
    }

    else
    {
        std::cout << "Connection to server failed!" << std::endl;
        return 1;
    }

    // sf::RenderWindow window(sf::VideoMode(640, 640), "Chess", sf::Style::Close);
    // window.setFramerateLimit(60);

    // TextureManager manager;
    // manager.load("images/whitePawn.png",   "WPawn");
    // manager.load("images/whiteKnight.png", "WKnight");
    // manager.load("images/whiteBishop.png", "WBishop");
    // manager.load("images/whiteRook.png",   "WRook");
    // manager.load("images/whiteQueen.png",  "WQueen");
    // manager.load("images/whiteKing.png",   "WKing");
    // manager.load("images/blackPawn.png",   "BPawn");
    // manager.load("images/blackKnight.png", "BKnight");
    // manager.load("images/blackBishop.png", "BBishop");
    // manager.load("images/blackRook.png",   "BRook");
    // manager.load("images/blackQueen.png",  "BQueen");
    // manager.load("images/blackKing.png",   "BKing");

    // Chess chess(window, manager, Common::Side::Black);   
    // Board& board = chess.getBoard();

    // while (window.isOpen())
    // {
    //     sf::Event event;

    //     while (window.pollEvent(event))
    //     {
    //         switch (event.type)
    //         {
    //             case sf::Event::Closed:
    //                 window.close();
    //                 break;
    //             case sf::Event::MouseButtonPressed:
    //                 board.onClick(event.mouseButton.button);
    //                 break;
    //             case sf::Event::MouseButtonReleased:
    //                 board.onRelease(event.mouseButton.button);
    //                 break;
    //             default:
    //                 break;
    //         }
    //     }

    //     board.drag();

    //     window.clear();
    //     window.draw(chess);
    //     window.display();
    // }

    return 0;
}