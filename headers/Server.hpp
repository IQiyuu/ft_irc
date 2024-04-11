#ifndef SERVIRC
#define SERVIRC

#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#include "Client.hpp"

# define MAX_CLIENTS 10
# define MESSAGE_SIZE 1024

class Server {
    private:
        int                 _port;
        std::string         _passwrd;
        int                 _socket;
        int                 _clientCounter;
        struct sockaddr_in  _addrServer;
        struct pollfd       _pfds[MAX_CLIENTS + 1];
        Client              *_clients[MAX_CLIENTS + 1];
        Server( void );
        
    
    public:
        Server( std::string, std::string );
        Server( const Server & );
        ~Server( void );
        Server &operator=( const Server & );

        void sendTo( std::string, std::string );
        void sendTo( int, std::string );

        void sendAll( std::string );

        void connect( void );
        void disconnect( void );
        void listening( void );
        int launch( void );
};

#endif