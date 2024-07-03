#include "Server.hpp"

Server::Server( std::string port, std::string pass ): 
    _port(port), _serverFd(0), _password(pass), _parser(new Parser(this)) {
    std::cout << "Server " << GREEN << "created" << RESET << std::endl;
}

Server::~Server( void ) {
    while (this->_channels.size() > 0) {
        delete this->_channels.back();
        this->_channels.pop_back();
    }
    while (this->_clients.size() > 0) {
        delete this->_clients.back();
        this->_clients.pop_back();
    }
    delete this->_parser;
    close(this->_serverFd);
    std::cout << "Server " << RED << "deleted" << RESET << std::endl;
}

/* on connecte un nouveau client */
int Server::connect( struct sockaddr_in clientAddr, socklen_t clientAddrLen) {
    int newSocket = accept(this->_serverFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (newSocket == -1) {
        std::cerr << "Accept failed" << std::endl;
        return ERROR;
    }
    pollfd nPfd = {newSocket, POLLIN, 0};
    this->_pfds.push_back(nPfd);
    
    char hostname[NI_MAXHOST];
    int res = getnameinfo((struct sockaddr *) &clientAddr, sizeof(clientAddr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
    if (res != 0)
        std::cout << "Error: " << RED << "getnameinfo crash" << RESET << std::endl;
    Client  *nClient = new Client(nPfd.fd, hostname);
    _clients.push_back(nClient);
    std::cout << "Server: " << YELLOW << "new connection" << RESET << std::endl;
    return SUCCESS;
}

/* on deconne le client fd */
void Server::disconnect( int fd ) {
    std::cout << "Server: " << YELLOW << "someone disapeared" << RESET << std::endl;
    Client *tmp = getClient(fd);
    /* supprime le fd du user deco */
    std::vector<pollfd>::iterator it2 = this->_pfds.begin();
    while (it2 != this->_pfds.end()) {
        if (it2->fd == fd) {
            this->_pfds.erase(it2);
            break ;
        }
        it2++;
    }
    /* on supprime l'instance du client deco dans ses channels */
    std::vector<Channel *>::iterator it4 = this->_channels.begin();
    while (it4 != this->_channels.end()) {
        std::vector<Client *> mm = (*it4)->getMembers();
        if ((std::find(mm.begin(), mm.end(), tmp) != mm.end())) {
            (*it4)->removeMember(tmp);
            /* on supprime les instances de channel si il n y a plus personne dessus */
            if ((*it4)->getMembers().size() == 0) {
                Channel *tmp_chan = *it4;
                this->_channels.erase(it4);
                delete tmp_chan;
            }
        }
        else
            ++it4;
    }
    /* on supprime l'instance du client deco */
    std::vector<Client *>::iterator it3 = this->_clients.begin();
    while (it3 != this->_clients.end()) {
        if ((*it3)->getSocketFd() == fd) {
            this->_clients.erase(it3);
            break ;
        }
        ++it3;
    }
    close(fd);
    delete tmp;
}

/* on deconne le client fd */
void Server::closeServer( void ) {
    /* on supprime tous les cannels */
    std::vector<Channel *>::iterator it4 = this->_channels.begin();
    while (it4 != this->_channels.end()) {
        Channel *tmp_chan = *it4;
        this->_channels.erase(it4);
        delete tmp_chan;
    }
    /* on supprime les instances des users */
    std::vector<Client *>::iterator it3 = this->_clients.begin();
    while (it3 != this->_clients.end()) {
        Client *tmp_cli = *it3;
        this->_clients.erase(it3);
        delete tmp_cli;
    }
    if (close(this->_serverFd) == -1)
        std::cout << "close error" << std::endl;
}

/* cherche le client avec son nickname*/
Client  *Server::getClient( std::string nname ) {
    std::vector<Client *>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); it++) {
        if (!nname.compare((*it)->getNickName()))
            return *it;
    }
    return NULL;
}

/* cherche le client avec son fd */
Client  *Server::getClient( int fd ) {
    std::vector<Client *>::iterator it;

    for (it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if ((*it)->getSocketFd() == fd)
            return *it;
    }
    return NULL;
}

/* cherche le channel avec son name  */
Channel *Server::getChannel(std::string args){
    std::vector<Channel*>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); it++)
    {
        std::cout << "|" << (*it)->getName().size() << "|" << args.size() << "|" << std::endl;
        if ((*it)->getName() == args)
            return *it;
    }
    return NULL;
}

std::vector<Client *>   Server::getClients( void ) const {
    return this->_clients;
}

std::vector<Channel *>  Server::getChannels( void ) const {
    return this->_channels;
}

std::string Server::getPass( void ) const {
    return this->_password;
}

void    Server::sendToConnected( Client *client, std::string msg ) {
    std::vector<Channel *>::iterator it;
    
    for (it = this->_channels.begin(); it != this->_channels.end(); ++it)
        if ((*it)->isConnected(client))
            (*it)->broadcast(msg, client);
}

/* ajoute un nouveau channel au server */
Channel *Server::createChannel( std::string name ) {
    Channel *chan;

    //std::cout << name << std::endl;
    chan = new Channel(name);
    this->_channels.push_back(chan);
    return (chan);
}

/* remove un channel de la liste des channels du server */
void    Server::removeChannel( Channel *chan ) {
    std::cout << "Server: " << YELLOW << "channel `" << chan->getName() << "` deleting not enough members." << RESET << std::endl;
    std::vector<Channel *>::iterator it = this->_channels.begin();
    while (it != this->_channels.end()) {
        if (chan == *it) {
            this->_channels.erase(it);
            delete chan;
            break ;
        }
    }
}

/* lance le server */
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
    serverAddr.sin_port = htons(atoi(this->_port.data()));
    fcntl(this->_serverFd, F_SETFL, O_NONBLOCK);
    if (bind(this->_serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == ERROR) {
        std::cout << "Error: " << RED << "binding failed." << RESET << std::endl;
        return ERROR;
    }

    /* ecoute les nouvelles connexions */
    if (listen(this->_serverFd, 5) == ERROR) {
        std::cout << "Error: " << RED << "listen failed." << RESET << std::endl;
        return ERROR;
    }

    std::cout << "Server: " << YELLOW << "launched." << RESET << std::endl;
    return SUCCESS;
}

/* le serveur crash car je rajoute un pollfd dans pfds pendant l'iteration. */
int Server::boucle( void ) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    std::vector<pollfd>::iterator it;

    // on ajoute le fd du server a ecouter (car le server recoit les requetes)
    pollfd serverPfd = {this->_serverFd, POLLIN, 0};

    this->_pfds.push_back(serverPfd);

    this->_state = LISTENING;
    std::cout << "Server: " << YELLOW << "listening " << RESET << "on port " << this->_port << std::endl;
    while (!sigint) {
        /* on attend un event sur les fd enregistres (serv fd compris) */
        int pfd = poll(this->_pfds.data(), this->_pfds.size(), POLL_TIMEOUT);
        if (pfd == ERROR)
            break ;
        /* on parcour tous nos pollfd pour voir si il y a des events */
        for (it = this->_pfds.begin(); it != this->_pfds.end(); it++) {
            /* si ya un event qui arrive */
            if (it->revents & POLLIN) {
                /* event sur le fd du serveur = nouvelle connexion */
                if (it->fd == this->_serverFd) {
                    /* on connecte le socket du nouvel user */
                    if (connect(clientAddr, clientAddrLen) == ERROR)
                        return ERROR;
                    break ;
                }
                else {
                    /* on recoit une requete */
                    char buf[BUF_SIZE];
                    bzero(buf, BUF_SIZE);
                    int byteRec = recv((*it).fd, buf, sizeof(buf), 0);
                    /* si la requete a 0 on deco */
                    if (byteRec <= 0) {
                        disconnect(it->fd);
                        break ;
                    }
                    /* execute les commandes */
                    if (this->_parser->parse(getClient(it->fd), buf))
                        break ;
                }
            }
        }
    }
    std::cout << "Server: " << YELLOW << "closing after ^C." << RESET << std::endl;
    closeServer();
    return SUCCESS;
}
