#include "Server.hpp"

Server::Server( std::string port, std::string passwrd ): _passwrd(passwrd), _clientCounter(0) {
    std::istringstream is(port);
    is >> this->_port;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    _pfds[0].fd = _socket;
    _pfds[0].events = POLLIN | POLLPRI;
    for (int i = 1; i < MAX_CLIENTS; i++)
        _pfds[i].fd = 0;
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
        dprintf(this->_pfds[i].fd, "Connection \033[33mClosed\033[0m\n");
        delete this->_clients[i];
    }
   
    std::cout << "Server \033[33mclosed\033[0m" << std::endl;
}

void Server::listening( void ) {
    while (true)
    {
        int pollResult = poll(this->_pfds, this->_clientCounter + 1, 10);
        if (pollResult > 0)
        {
            if (this->_pfds[0].revents & POLLIN)
            {
                struct sockaddr_in cliaddr;
                socklen_t addrlen = sizeof(cliaddr);
                int client_socket = accept(this->_socket, (struct sockaddr *)&cliaddr, &addrlen);

                char ipFrom[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(cliaddr.sin_addr), ipFrom, INET_ADDRSTRLEN);

                printf("accept success %s\n", inet_ntoa(cliaddr.sin_addr));
                for (int i = 1; i < MAX_CLIENTS; i++)
                {
                    if (this->_pfds[i].fd == 0)
                    {
                        this->_pfds[i].fd = client_socket;
                        this->_pfds[i].events = POLLIN | POLLPRI;
                        this->_clientCounter++;
                        break;
                    }
                }
                //sendAll(this->_pfds, "", "SERVER");
            }
            for (int i = 1; i < MAX_CLIENTS; i++)
            {
                if (this->_pfds[i].fd > 0 && this->_pfds[i].revents & POLLIN)
                {
                    char buf[MESSAGE_SIZE];
                    int bufSize = read(this->_pfds[i].fd, buf, MESSAGE_SIZE - 1);
                    if (bufSize == -1)
                    {
                        printf("CLOSED\n");
                        this->_pfds[i].fd = 0;
                        this->_pfds[i].events = 0;
                        this->_pfds[i].revents = 0;
                        this->_clientCounter--;
                    }
                    else if (bufSize == 0)
                    {
                        printf("CLOSED\n");
                        this->_pfds[i].fd = 0;
                        this->_pfds[i].events = 0;
                        this->_pfds[i].revents = 0;
                        this->_clientCounter--;
                    }
                    else
                    {
                        buf[bufSize] = '\0';
                        printf("From client: %s\n", buf);

                        struct sockaddr_in addrSender;
                        socklen_t addrlen2 = sizeof(addrSender);
                        getsockname(this->_pfds[i].fd, reinterpret_cast<struct sockaddr*>(&addrSender), &addrlen2);
                        char ipFrom[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &(addrSender.sin_addr), ipFrom, INET_ADDRSTRLEN);

                        for (int x = 1; x < MAX_CLIENTS; x++) {
                            /* fetsockname, getprotobyname, gethostbyname, getaddrinfo*/
                            if (x != i && this->_pfds[x].fd != 0) {
                                write(this->_pfds[x].fd, ipFrom, strlen(ipFrom));
                                write(this->_pfds[x].fd, ": ", 2);
                                write(this->_pfds[x].fd, buf, strlen(buf));
                            }
                        }
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