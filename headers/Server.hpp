
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

        Parser                  *_parser;

        Server( void );
        Server( const Server & );
        Server  *operator=( const Server & );
    
    public:
        Server( std::string, std::string );
        ~Server( void );

        /* recupere un client par rapport a son nickname */
        Client  *getClient( std::string );
        /* recupere un client par rapport a son int */
        Client  *getClient( int );
        /* recupere le channel */
        Channel *getChannel( std::string );

        /* connecte un nouveau Client au server */
        int    connect( std::vector<pollfd> *, struct sockaddr_in, socklen_t );
        /* deconnecte un Client du server */
        void    disconnect( std::vector<pollfd> *, int );
        /* cree un channel*/
        void    newChannel(std::string);
        /* creer un nouveau channel et le retourne */
        Channel *createChannel( std::string, Client * );

        /* parse la requete du client */
        void    parse( void );

        /* lance le server */
        int    launch( void );
        /* met le server sur ecoute */
        int    boucle( void );

};

#endif