#ifndef COMMANDIRC
#define COMMANDIRC

#include "ft_irc.hpp"
#include "Client.hpp"

class Command {
    protected:
        Server *_serv;

    public:
        Command(void);
        ~Command(void);
        virtual void execute( Client *, std::string ) = 0;
};

class Ban: public Command {
    public:
        void execute( Client *, std::string );
};

class Nick: public Command {
    public:
        void execute( Client *, std::string );
};

#endif