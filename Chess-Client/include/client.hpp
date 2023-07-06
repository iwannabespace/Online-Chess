#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>

class Client
{
    public:
        Client(const sf::IpAddress& host, unsigned short port);
        ~Client();
        bool connect();
        bool send(const std::string& move);
        bool connected() const;
    private:
        sf::TcpSocket socket;
        sf::IpAddress host;
        unsigned short port;
        bool _connected;
};

#endif