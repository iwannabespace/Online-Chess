#include "../include/client.hpp"

Client::Client(const sf::IpAddress& host, unsigned short port)
    : host(host), port(port), _connected(false)
{
}

Client::~Client()
{
}

bool Client::connect()
{
    return (_connected = (socket.connect(host, port) == sf::Socket::Done));
}

bool Client::send(const std::string& move)
{
    sf::Packet packet;
    packet << move;
    
    sf::Socket::Status status = socket.send(packet);

    if (status == sf::Socket::Status::Disconnected)  
    {   
        socket.disconnect();
        _connected = false;
    }

    return status == sf::Socket::Status::Done;
}

bool Client::connected() const
{
    return _connected;
}