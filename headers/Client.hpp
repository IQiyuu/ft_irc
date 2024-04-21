#ifndef CLIENTIRC
#define CLIENTIRC

#include "ft_irc.hpp"

class Client {
    private:

        int _socketFd;
        std::string _realname;
        std::string _username;
        std::string _nickname;
        int _state;
        
        Client &operator=( const Client & );

    public:
        Client(void);
        Client( const Client & );
        // Cree un client avec le name, le nickname, le username et socketfd 
        Client (std::string, std::string, std::string, int);
        Client( int fd );
        ~Client( void );

        //getter
        std::string getNickName(void);
        std::string getRealname(void);
        std::string getUsername(void);
        int getSocketFd(void);
        int getState( void );

        std::string getPrefix( void );

        //setter
        void setNickName(std::string);
        void setUsername(std::string);
        void setRealname(std::string);
        void    setState( int );

        /* send messages */
        void    sendMsg( std::string );
        void    sendReply( std::string msg );

};

#endif