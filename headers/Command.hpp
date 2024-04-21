#ifndef COMMANDIRC
#define COMMANDIRC

#include "ft_irc.hpp"

class Command {
    protected:
        Server *_serv;

    public:
        Command( Server * );
        virtual ~Command(void);
        virtual void execute( Client *, std::string ) = 0;
};

class Ban: public Command {
    public:
        Ban( Server * );
        ~Ban( void );
        void execute( Client *, std::string );
};

class Invite: public Command {
    public:
        Invite( Server * );
        ~Invite( void );
        void execute( Client *, std::string );
};

class Join: public Command {
    public:
        Join( Server * );
        ~Join( void );
        void execute( Client *, std::string );
};

class Kick: public Command {
    public:
        Kick( Server * );
        ~Kick( void );
        void execute( Client *, std::string );
};

class Mode: public Command {
    public:
        Mode( Server * );
        ~Mode( void );
        void execute( Client *, std::string );
};

class Nick: public Command {
    public:
        Nick( Server * );
        ~Nick( void );
        void execute( Client *, std::string );
};

class Pass: public Command {
    public:
        Pass( Server * );
        ~Pass( void );
        void execute( Client *, std::string );
};

class Ping: public Command {
    public:
        Ping( Server * );
        ~Ping( void );
        void execute( Client *, std::string );
};

class Pong: public Command {
    public:
        Pong( Server * );
        ~Pong( void );
        void execute( Client *, std::string );
};

class PrivMsg: public Command {
    public:
        PrivMsg( Server * );
        ~PrivMsg( void );
        void execute( Client *, std::string );
};

class User: public Command {
    public:
        User( Server * );
        ~User( void );
        void execute( Client *, std::string );
};


#endif