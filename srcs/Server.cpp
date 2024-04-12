#include "Server.hpp"

Server::Server( std::string port, std::string passwrd ): _passwrd(passwrd), _clientCounter(0) {
    std::cout << "Server \033[32mcreated\033[0m" << std::endl;
    std::istringstream is(port);
    is >> this->_port;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    _pfds[0].fd = _socket;
    _pfds[0].events = POLLIN | POLLPRI;
    for (int i = 1; i < MAX_CLIENTS; i++) {
        _pfds[i].fd = 0;
        _clients[i] = NULL;
    }
    if (launch())
        std::cout << "Server \033[31mCRASHED\033[0m" << std::endl;
}

Server::Server( const Server &ref ) {
    *this = ref;
}

Server &Server::operator=( const Server &ref ) {
    this->_port = ref._port;
    this->_passwrd = ref._passwrd;
    close(this->_socket);
    this->_socket = ref._socket;
    this->_clientCounter = ref._clientCounter;
    return *this;
}

Server::~Server( void ) {
    close(this->_socket);
    for(int i = 1; i < MAX_CLIENTS; i++) {
        if (this->_pfds[i].fd > 0) {
            dprintf(this->_pfds[i].fd, "Connection \033[33mClosed\033[0m\n");
            delete this->_clients[i];
        }
    }
   
    std::cout << "Server \033[33mclosed\033[0m" << std::endl;
}

/* utils */
int Server::wichClientHave( int ip ) {
    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (this->_clients[i] && this->_clients[i]->getIp() == ip)
            return i;
    }
    return -1;
}

int Server::getIpFromIndex( int i ) {
    struct sockaddr_in addrSender;
    socklen_t addrlen = sizeof(addrSender);
    getsockname(this->_pfds[i].fd, reinterpret_cast<struct sockaddr*>(&addrSender), &addrlen);
    char ipFrom[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addrSender.sin_addr), ipFrom, INET_ADDRSTRLEN);
    return Client::ipStoI(ipFrom);
}

int Server::getIndexFromIp( int ip ) {
    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (this->_clients[i] && this->_clients[i]->getIp() == ip)
            return i;
    }
    return -1;
}

Client &Server::getClientByUsername( std::string uname ) {
    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (this->_clients[i] && this->_clients[i]->getUsername() == uname)
            return *(this->_clients[i]);
    }
    throw "Client not found";
}

std::string Server::getPasswrd( void ) {
    return this->_passwrd;
}

bool    Server::ipAlreadyConnected( int ip ) {
    for (int i = 1; i < MAX_CLIENTS; i++)
        if (this->_clients[i] && this->_clients[i]->getIp() == ip)
            return true;
    return false;
}

/* sends */
void Server::sendTo( int ipFrom, int ipTo, std::string msg ) {
    int clientNb = wichClientHave(ipTo);

    if (clientNb < 0) {
        std::cout << "Unknowed sender" << std::endl;
        return ;
    }

    dprintf(this->_pfds[clientNb].fd, "%d: %s\n", ipFrom, msg.data());
}

void Server::sendAll( int ip, std::string msg ) {
    int clientNb = wichClientHave(ip);
    if (clientNb < 0) {
        std::cout << "Unknowed sender" << std::endl;
        return ;
    }

    struct sockaddr_in addrSender;
    socklen_t addrlen = sizeof(addrSender);
    getsockname(this->_pfds[clientNb].fd, reinterpret_cast<struct sockaddr*>(&addrSender), &addrlen);
    char ipFrom[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addrSender.sin_addr), ipFrom, INET_ADDRSTRLEN);

    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (this->_pfds[i].fd > 0 && i != clientNb)
            dprintf(this->_pfds[i].fd, "%s: %s\n", this->_clients[clientNb]->getUsername().data(), msg.data());
    }
}

/* boucle */
int Server::connect( void ) {
    struct sockaddr_in cliaddr;
    socklen_t addrlen = sizeof(cliaddr);
    int client_socket = accept(this->_socket, (struct sockaddr *)&cliaddr, &addrlen);

    char ipFrom[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(cliaddr.sin_addr), ipFrom, INET_ADDRSTRLEN);

    if (ipAlreadyConnected(Client::ipStoI(ipFrom))) {
        sendTo(getIpFromIndex(0), Client::ipStoI(ipFrom), "User connected with the same IP");
        disconnect(getIndexFromIp(Client::ipStoI(ipFrom)));
    }

    if (this->_clientCounter == MAX_CLIENTS + 1) {
        sendTo(getIpFromIndex(0), Client::ipStoI(ipFrom), "Too much users connected");
        close(client_socket);
        return 1;
    }

   std::cout << "\033[32maccept success\033[0m " << inet_ntoa(cliaddr.sin_addr) << std::endl;
    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (this->_pfds[i].fd == 0) {
            this->_pfds[i].fd = client_socket;
            this->_pfds[i].events = POLLIN | POLLPRI;
            this->_clients[i] = new Client("Random", Client::ipStoI(ipFrom), client_socket);
            this->_clientCounter++;
            break;
        }
    }
    sendAll(Client::ipStoI(ipFrom), "now connected");
    return 0;
}

void Server::disconnect( int i ) {
    std::cout << getIpFromIndex(i) << " \033[33mCLOSED\033[0m" << std::endl;
    sendAll(getIpFromIndex(i), "now disconnected");
    this->_pfds[i].fd = 0;
    this->_pfds[i].events = 0;
    this->_pfds[i].revents = 0;
    delete this->_clients[i];
    this->_clients[i] = NULL;
    this->_clientCounter--;
}

void Server::listening( void ) {
    while (true)
    {
        int pollResult = poll(this->_pfds, this->_clientCounter + 1, 10);
        if (pollResult > 0)
        {
            if (this->_pfds[0].revents & POLLIN)
                if (connect())
                    continue ;
            for (int i = 1; i < MAX_CLIENTS; i++)
            {
                if (this->_pfds[i].fd > 0 && this->_pfds[i].revents & POLLIN)
                {
                    char buf[MESSAGE_SIZE];
                    int bufSize = read(this->_pfds[i].fd, buf, MESSAGE_SIZE - 1);
                    if (bufSize <= 0)
                        disconnect(i);
                    else if (this->_pfds[i].fd > 0)
                    {
                        buf[bufSize] = '\0';
                        std::cout << "From client: " << buf << std::endl;

                        Parser p;
                        p.parse(buf, *this, *(this->_clients[i]));
                    }
                }
            }
        }
    }
}

int Server::launch( void ) {
    this->_addrServer.sin_family = AF_INET;
    this->_addrServer.sin_port = htons(_port);
    this->_addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(this->_socket, (struct sockaddr *) &this->_addrServer, sizeof(this->_addrServer)) < 0) {
        std::cout << "Binding \033[31mfailed\033[0m" << std::endl;
        return 1;
    }

    /* creer une longueur max a la file d attente des demandes de connexion */
    if (listen(this->_socket, 10) < 0) {
        std::cout << "Listening \033[31mfailed\033[0m" << std::endl;
        return 1;
    }
    std::cout << "Server \033[33mReady\033[0m on port " << this->_port << std::endl;
    return 0;
}