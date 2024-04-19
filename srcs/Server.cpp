#include "Server.hpp"

Server::Server( std::string port, std::string pass ): _port(port), _socketFd(0), _password(pass) {
    std::cout << "Server " << GREEN << "created" << RESET << std::endl;
}

Server::~Server( void ) {
    for (std::vector<Channel *>::iterator *it; it != this->_channels.end(); it++) {
        delete *it;
    }
    for (std::vector<Client *>::iterator *it; it != this->_clients.end(); it++) {
        delete *it;
    }
    std::cout << "Server " << RED << "deleted" << RESET << std::endl;
}

int Server::launch( void ) {
    struct sockaddr_in serverAddr;

    /* on initialise la socket du serveur */
    if ((this->_serverFd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        std::cout << "Error: " << RED << "socket failed" << RESET;
        return ERROR;
    }

    /* on bind la socket sur le port */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(this->_port);
    if (bind(this->_serverFd, (struct sockaddr_in *)&serverAddr, sizeof(serverAddr)) == ERROR) {
        std::cout << "Error: " << RED << " binding failed" << RESET << std::endl;
        return ERROR;
    }

    /* ecoute les nouvelles connexions */
    if (listen(this->_serverFd, 5) == ERROR) {
        std::cout << "Error: " << RED << "listen failed" << RESET << std::endl;
        return ERROR;
    }

    std::cout << "Server: " << YELLOW << " launched " << RESET << "on port" << this->_port << std::endl;
}

int listen( void ) {
    /* fd qu'on enregistre et qu'on va ecouter */
    std::vector<pollfd> pfds;
    int                 clientFd;
    struct sockaddr_in clientAddr;

    // on ajoute le fd du server a ecouter (car le server recoit les requetes)
    pfds.push_back({this->serverFd, POLLIN, 0});
    this->_state = LISTENING;
    while (this->_state == LISTENING) {
        // on attend un event sur les fd enregistres (serv fd compris)
        int pfd = poll(pfds.data(), pfds.size(), -1)
        if ((clientFd = accept(server_fd, (struct sockaddr *)&clientAddr, sizeof(clientAddr))) == -1) {
            std::cout << "Error: " << RED << "accept error" << RESET << std::endl;
            return ERROR;
        }
    }
}