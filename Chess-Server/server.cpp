#include "server.hpp"
#include <iostream>

Server::Server(unsigned short port)
    : port(port), playerCount(0)
{
}

Server::~Server()
{
}

bool Server::listen()
{
    if (listener.listen(port) != sf::Socket::Done)
        return false;

    return true;
}

void Server::run()
{
    if (this->listen())
    {
        selector.add(listener);

        while (true)
        {
            if (selector.wait())
            {
                if (playerCount < 2 && selector.isReady(listener))
                {
                    sf::TcpSocket* player;
                    player = new sf::TcpSocket;

                    if (listener.accept(*player) == sf::Socket::Done)
                    {
                        players[playerCount++] = player;
                        selector.add(*player);
                        std::cout << "New connection from " << player->getRemoteAddress() << std::endl;
                    }

                    else
                        delete player;
                }
                
                else
                {
                    for (size_t i = 0; i < players.size(); i++)
                    {
                        sf::TcpSocket* player = players[i];

                        if (selector.isReady(*player))
                        {
                            sf::Packet recvPacket;
                            sf::Packet sendPacket;

                            sf::Socket::Status status = player->receive(recvPacket);

                            if (status == sf::Socket::Done)
                            {
                                std::string move;
                                recvPacket >> move;
                                std::cout << "Player " << (!i ? "white -> " : "black -> ")  << move << std::endl;
                            }

                            else if (status == sf::Socket::Disconnected)
                            {
                                std::cout << "Client disconnected -> " << player->getRemoteAddress() << std::endl;
                                selector.remove(*player);
                                delete player;
                                players[i] = nullptr;
                            }
                        }
                    }
                }
            }
        }
    }
}