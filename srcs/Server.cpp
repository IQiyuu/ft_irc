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

int Server::connect( std::vector<pollfd> *pfds, struct sockaddr_in clientAddr, socklen_t clientAddrLen) {
    int newSocket = accept(this->_serverFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (newSocket == -1) {
        std::cerr << "Accept failed" << std::endl;
        return ERROR;
    }
    pollfd nPfd = {newSocket, POLLIN, 0};
    pfds->push_back(nPfd);
    _clients.push_back(new Client());
    std::cout << "Server: " << YELLOW << "new connection" << RESET << std::endl;
    return SUCCESS;
}

void Server::disconnect( std::vector<pollfd> *pfds, int fd) {
    std::cout << "Server: someone disapear" << std::endl;
    close(fd);
    /* supprime le fd du user deco */
    std::vector<pollfd>::iterator it2 = pfds->begin();
    while (it2 != pfds->end()) {
        if (it2->fd == fd) {
            it2 = pfds->erase(it2);
            break ;
        }
        ++it2;
    }
}

Client  *Server::getClient( int fd ) {
    std::vector<Client *>::iterator it;

    for (it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if ((*it)->getSocketFd() == fd)
            return *it;
    }
    return NULL;
}

Channel *Server::channelExist(std::string args){
    std::vector<Channel*>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); it++)
    {
        if ((*it)->getName() == args)
            return *it;
    }
    return NULL;
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
    fcntl(this->_serverFd, F_SETFL, O_NONBLOCK);
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

void Server::newChannel(std::string args)
{
    if (args.size() > 50)
    {
        std::cout << "Error: " << RED << " max length to create a channel is 50." << RESET << std::endl;
        return ;
    }
    if (args[0] != '#')
    {
        std::cout << "Error: " << RED << " the first character must be a #." << RESET << std::endl;
        return ;
    }
    for (int i = 0; i <= (int)args.size(); i++)
    {
        if (!isalnum(args[i]) && !isalnum(args[i]) && args[i] != '_' && args[i] != '-' && args[i] != '.')
        {
            std::cout << "Error: " << RED << " wrong character in channel name." << RESET << std::endl;
            return ;
        }
    }
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
        for (it = pfds.begin(); it != pfds.end(); ++it) {
            if (it->revents == 0)
                continue ;
            /* si ya un event qui arrive */
            if (it->revents & POLLIN) {
                /* event sur le fd du serveur = nouvelle connexion */
                if (it->fd == this->_serverFd) {
                    /* on connecte le socket du nouvel user */
                    if (connect(&pfds, clientAddr, clientAddrLen) == ERROR)
                        return ERROR;
                    break ;
                }
                else {
                    char buf[BUF_SIZE];
                    int byteRec = recv((*it).fd, buf, sizeof(buf), 0);
                    if (byteRec <= 0) {
                        disconnect(&pfds, it->fd);
                        break ;
                    }
                    std::cout << "Server received: " << buf << std::endl;
                    /* execute les commandes */
                }
            }
            else {
                std::cout << "someone deco" << std::endl;
            }
        }
    }
    return SUCCESS;
}