#ifndef CLIENTIRC
#define CLIENTIRC

#include <iostream>
#include <poll.h>
#include <netinet/in.h>
#include <sstream>
#include <unistd.h>
#include <ctime>

class Client {
    private:
        std::string     _username;
        int             _ip;
        time_t          _connectionTime;
        struct pollfd   _pfd;
        bool            _locked;
        Client( void );
    
    public:
        Client( std::string, int, int );
        Client( const Client & );
        Client &operator=( const Client & );
        ~Client( void );

        std::string getUsername( void ) const;
        bool        getLock( void ) const;
        int         getIp( void ) const;
        struct pollfd getPollFd( void ) const;

        void        unlock( void );
        std::string ipToString( void ) const;
        std::string whoAmI( void ) const;
};


#endif