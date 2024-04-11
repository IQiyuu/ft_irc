#include "Server.hpp"

int main( int ac, char *av[] ) {
    if (ac != 3) {
        std::cout << "Bad parameters! The program should be launched like: `./ircserv <port> <username>`" << std::endl;
        return 0;
    }

    Server serv(av[1], av[2]);
    return 0;
}