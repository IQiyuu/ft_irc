#ifndef SERVIRC
#define SERVIRC

#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#include "Client.hpp"
#include "Parser.hpp"

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
        
        
    
    public:
        Server( void ) {}
        Server( std::string, std::string );
        Server( const Server & );
        ~Server( void );
        Server &operator=( const Server & );

        /* Fct to send messages */
        void sendTo( int, int, std::string );
        void sendAll( int, std::string );

        /* boucles and actions */
        int connect( void );
        void disconnect( int );
        void listening( void );
        int launch( void );

        /* utils */
        int getIpFromIndex( int );
        Client &getClientByUsername( std::string );
        int wichClientHave( int );
        std::string getPasswrd( void );
        bool ipAlreadyConnected( int );
        int getIndexFromIp( int );
};

#endif