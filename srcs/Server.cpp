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
            it2 = this->_pfds.erase(it2);
            break ;
        }
        it2++;
    }
    /* on supprime l'instance du client deco dans ses channels */
    std::vector<Channel *>::iterator it4 = this->_channels.begin();
    while (it4 != this->_channels.end()) {
        std::vector<Client *> mm = (*it4)->getMembers();
        if ((std::find(mm.begin(), mm.end(), tmp) != mm.end()))
            (*it4)->removeMember(tmp);
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
    
    for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
        std::vector<Client *> mm = (*it)->getMembers();
        if (std::find(mm.begin(), mm.end(), client) != mm.end()) {
            (*it)->broadcast(msg, client);
        }
    }
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

/* ajoute un nouveau channel au server */
Channel *Server::createChannel( std::string name ) {
    Channel *chan;

    chan = new Channel(name);
    this->_channels.push_back(chan);
    return (chan);
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
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    std::vector<pollfd>::iterator it;

    // on ajoute le fd du server a ecouter (car le server recoit les requetes)
    pollfd serverPfd = {this->_serverFd, POLLIN, 0};

    this->_pfds.push_back(serverPfd);

    this->_state = LISTENING;
    std::cout << "Server: " << YELLOW << "listening " << RESET << "on port " << this->_port << std::endl;
    while (this->_state == LISTENING) {
        /* on attend un event sur les fd enregistres (serv fd compris) */
        int pfd = poll(this->_pfds.data(), this->_pfds.size(), POLL_TIMEOUT);
        if (pfd == ERROR) {
            if (sigint) {
                this->_state = EXITING;
                std::cout << "Server: " << YELLOW << "exiting " << RESET << "after ^C" << std::endl;
                break ;
            }
            std::cout << "Error: " << RED << "poll crashed" << RESET << std::endl;
            return ERROR;
        }
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
                    /* si la requete a 0b on deco */
                    if (byteRec <= 0) {
                        disconnect(it->fd);
                        break ;
                    }
                    std::cout << "=Server received: " << buf << "=" << std::endl;
                    /* execute les commandes */
                    if (this->_parser->parse(getClient(it->fd), buf))
                        break ;
                }
            }
        }
    }
    return SUCCESS;
}