#ifndef COMMANDIRC
#define COMMANDIRC

#include "ft_irc.hpp"

class Command {
    protected:
        Client *sender;

    public:
        Command(void);
        ~Command(void);
        void execute( );
};

class Ban: public Command {
    public:

};

#endif