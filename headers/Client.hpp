#ifndef CLIENTIRC
#define CLIENTIRC

#include "ft_irc.hpp"

class Client {
    private:
        /* socket du client pour communiquer */
        int _socketFd;
        /* aucune idee du realname */
        std::string _realname;
        /* aucune idee du username */
        std::string _username;
        /* nickname du client que tout le monde voit (modifiable) */
        std::string _nickname;
        /* hostname du client */
        std::string _hostname;
        /* state du client (pour voir si il est log) */
        int _state;
        /* ajouter un truc pour les modes */
        
        Client &operator=( const Client & );

    public:
        Client(void);
        Client( const Client & );
        /* Cree un client avec nickname, username et socketfd (ca arrivera jamais) */ 
        Client (std::string, std::string, std::string, int);
        /* Cree un client avec son hostname et son fd */
        Client( int, std::string );
        /* creer un client avec sa socket (son fd) */
        Client( int fd );
        ~Client( void );

        /************************************/
        /*             GETTERS              */
        /************************************/
        std::string getNickName(void);
        std::string getRealname(void);
        std::string getUsername(void);
        std::string getHostName( void );
        int         getSocketFd(void);
        int         getState( void );
        std::string getPrefix( void );

        /************************************/
        /*              SETTER              */
        /************************************/
        void    setNickName(std::string);
        void    setUsername(std::string);
        void    setRealname(std::string);
        void    setHostname( std::string );
        void    setState( int );

        /************************************/
        /*              SENDERS             */
        /************************************/
        void    sendMsg( std::string );
        void    sendReply( std::string msg );

        void    welcome( void );
};

/* afficher un client (debug) */
std::ostream &operator<<(std::ostream &, Client & );

#endif