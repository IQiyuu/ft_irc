
#ifndef SERVIRC
#define SERVIRC

#include "ft_irc.hpp"

class Server {
    private:
        /* etat actuel du server */
        int                     _state;
        /* liste des channels existants du server */
        std::vector<Channel *>  _channels;
        /* liste des clients connectes du server */
        std::vector<Client *>   _clients;
        /* bah le port du server */
        std::string             _port;
        /* le fd de la socket du server */
        int                     _serverFd;
        /* le mdp pour se co au server */
        std::string             _password;
        /* la liste des pollfd (pour ecouter les events) */
        std::vector<pollfd>     _pfds;

        /* va te faire si tu comprends pas */
        Parser                  *_parser;

        Server( void );
        Server( const Server & );
        Server  *operator=( const Server & );
    
    public:
        Server( std::string, std::string );
        ~Server( void );

        /************************************/
        /*              GETTERS             */
        /************************************/

        /* recupere un client par rapport a son nickname */
        Client  *getClient( std::string );
        /* recupere un client par rapport a son int */
        Client  *getClient( int );
        /* recupere le channel */
        Channel *getChannel( std::string );
        /* recupere la liste des clients (connectes) du server */
        std::vector<Client *>   getClients( void ) const;
        /* recupere la liste des channels (existants) du server */
        std::vector<Channel *>  getChannels( void ) const;

        void  sendToConnected( Client *, std::string );

        /************************************/
        /*               UTILS              */
        /************************************/

        /* connecte un nouveau Client au server */
        int    connect( struct sockaddr_in, socklen_t );
        /* deconnecte un Client du server */
        void    disconnect( int );
        /* cree un channel*/
        void    newChannel(std::string);
        /* creer un nouveau channel et le retourne */
        Channel *createChannel( std::string );

        /* parse la requete du client */
        void    parse( void );

        /************************************/
        /*               JSP                */
        /************************************/

        /* lance le server */
        int    launch( void );
        /* met le server sur ecoute */
        int    boucle( void );

};

#endif