#ifndef SERVIRC
#define SERVIRC

#include "ft_irc.hpp"

class Server {
    private:
        int                     _state;
        std::vector<Channel *>  _channels;
        std::vector<Client *>   _clients;
        std::string             _port;
        int                     _serverFd;
        std::string             _password;

        Server( void );
        Server( const Server & );
        operator=( const Server & );
    
    public:
        Server( std::string, std::string );
        ~Server( void );

        /* recupere un client par rapport a son nickname */
        Client  *getClient( std::string );
        /* recupere un client par rapport a son int */
        Client  *getClient( int );
        /* verifie si le channel existe */
        Channel *channelExist( std::string );

        /* connecte un nouveau Client au server */
        void    connect( void );
        /* deconnecte un Client du server */
        void    disconnect( void );

        /* parse la requete du client */
        void    parse( void );

        /* lance le server */
        int    launch( void );
        /* met le server sur ecoute */
        int    listen( void );
};

#endif