#include "Server.hpp"

Server::Server( std::string port, std::string pass ): _port(port), _serverFd(0), _password(pass) {
    std::cout << "Server " << GREEN << "created" << RESET << std::endl;
}

Server::~Server( void ) {
    for (std::vector<Channel *>::iterator it; it != this->_channels.end(); it++) {
        delete *it;
    }
    for (std::vector<Client *>::iterator it; it != this->_clients.end(); it++) {
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
    serverAddr.sin_port = htons(6666);
    if (bind(this->_serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == ERROR) {
        std::cout << "Error: " << RED << " binding failed" << RESET << std::endl;
        return ERROR;
    }

    /* ecoute les nouvelles connexions */
    if (listen(this->_serverFd, 5) == ERROR) {
        std::cout << "Error: " << RED << "listen failed." << RESET << std::endl;
        return ERROR;
    }

    std::cout << "Server: " << YELLOW << "launched" << RESET << std::endl;
    return SUCCESS;
}

/* le serveur crash car je rajoute un pollfd dans pfds pendant l'iteration. */
int Server::boucle( void ) {
    /* fd qu'on enregistre et qu'on va ecouter */
    std::vector<pollfd> pfds;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    std::vector<pollfd>::iterator it;

    // on ajoute le fd du server a ecouter (car le server recoit les requetes)
    pollfd serverPfd = {this->_serverFd, POLLIN, 0};

    pfds.push_back(serverPfd);

    this->_state = LISTENING;
    std::cout << "Server: " << YELLOW << "listening " << RESET << "on port " << this->_port << std::endl;
    while (this->_state == LISTENING) {
        
        // on attend un event sur les fd enregistres (serv fd compris)
        int pfd = poll(pfds.data(), pfds.size(), POLL_TIMEOUT);
        if (pfd == ERROR) {
            std::cout << "Error: " << RED << "poll crashed" << RESET << std::endl;
            return ERROR;
        }
        std::vector<pollfd> newPfds;
        for (it = pfds.begin(); it != pfds.end(); it++) {
            if (it->revents == 0)
                continue;
            // si ya un event qui arrive
            if (it->revents & POLLIN) {
                // nouvelle connexion
                if (it->fd == this->_serverFd) {
                    /* on connecte le socket du nouvel user */
                    int newSocket = accept(this->_serverFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
                    if (newSocket == -1) {
                        std::cerr << "Accept failed" << std::endl;
                        continue;
                    }
                    /* on l'ajoute /!\ faudra verifier le nombre /!\ */
                    pollfd nPfd = {newSocket, POLLIN, 0};
                    newPfds.push_back(nPfd);
                    _clients.push_back(new Client());
                    std::cout << "Server: " << YELLOW << "new connection" << RESET << std::endl;
                }
            }
            else {
            }
        }
        pfds.insert(pfds.end(), newPfds.begin(), newPfds.end());
    }
    return SUCCESS;
}