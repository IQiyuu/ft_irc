#ifndef CLIENTIRC
#define CLIENTIRC

#include "ft_irc.hpp"

class Client {
    private:

        int _socketFd;
        std::string _realname;
        std::string _username;
        std::string _nickname;

        Client(void);
        ~Client(void);
        operator=(const &Client);
    public: 
        // Cree un client avec le name, le nickname, le username et socketfd 
        Client (std::string, std::string, std::string, int);

        //getter
        std::string getName(void);
        std::string getRealname(void);
        std::string getUsername(void);
        int getSocketFd(void);

        //setter
        void setName(std::string);
        void setUsername(std::string);
        void setRealname(std::string);

};

#endif