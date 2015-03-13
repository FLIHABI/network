#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    boost::asio::io_service io_service;

    tcp::endpoint endpoint(tcp::v4(), 7171); // (1)
    tcp::acceptor acceptor(io_service, endpoint);

    while (1)
    {
        tcp::iostream stream;
        acceptor.accept(*stream.rdbuf()); // (2)
        stream << "Bienvenue sur le serveur ! "<< std::endl;
    }

    return 0;
}
