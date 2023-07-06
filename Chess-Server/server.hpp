#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <array>

class Server
{
    public:
        Server(unsigned short port);
        ~Server();
        bool listen();
        void run();
    private:
        unsigned short port;
        sf::TcpListener listener;
        sf::SocketSelector selector;
        std::array<sf::TcpSocket*, 2> players;
        size_t received;
        size_t playerCount;
};

#endif