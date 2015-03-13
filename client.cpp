#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    tcp::iostream s("127.0.0.1", "7171"); //(1)
    std::string line;
    std::getline(s, line); // (2)
    std::cout << line << std::endl;

    return 0;
}
