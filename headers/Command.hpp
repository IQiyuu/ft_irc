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

/* Ban un mec */
class Ban: public Command {
    public:
        Ban( Server * );
        ~Ban( void );
        void execute( Client *, std::string );
};

/* liste les capacites du serv (j'ai mit none a voir) */
class Cap: public Command {
    public:
        Cap( Server * );
        ~Cap( void );
        void execute( Client *, std::string );
};

/* invite un mec dans le channel */
class Invite: public Command {
    public:
        Invite( Server * );
        ~Invite( void );
        void execute( Client *, std::string );
};

/* rejoind le channel specifier, le creer si vide */
class Join: public Command {
    public:
        Join( Server * );
        ~Join( void );
        void execute( Client *, std::string );
};

/* kick un mec du channel */
class Kick: public Command {
    public:
        Kick( Server * );
        ~Kick( void );
        void execute( Client *, std::string );
};

/* aucune idee chiant les mode un peu */
class Mode: public Command {
    public:
        Mode( Server * );
        ~Mode( void );
        void execute( Client *, std::string );
};

/* change le nickname du bougre */
class Nick: public Command {
    public:
        Nick( Server * );
        ~Nick( void );
        void execute( Client *, std::string );
};

/* leave un channel */
class Part: public Command {
    public:
        Part( Server * );
        ~Part( void );
        void execute( Client *, std::string );
};

/* entre le mot de passe */
class Pass: public Command {
    public:
        Pass( Server * );
        ~Pass( void );
        void execute( Client *, std::string );
};

/* bah ping quoi */
class Ping: public Command {
    public:
        Ping( Server * );
        ~Ping( void );
        void execute( Client *, std::string );
};

/* bah reponse a ping */
class Pong: public Command {
    public:
        Pong( Server * );
        ~Pong( void );
        void execute( Client *, std::string );
};

/* message prive a un mec / un chan */
class PrivMsg: public Command {
    public:
        PrivMsg( Server * );
        ~PrivMsg( void );
        void execute( Client *, std::string );
};

/* quitte le serveur */
class Quit: public Command {
    public:
        Quit( Server * );
        ~Quit( void );
        void execute( Client *, std::string );
};

/* donne les infos sur un client (soit je crois) */
class User: public Command {
    public:
        User( Server * );
        ~User( void );
        void execute( Client *, std::string );
};

/* donne les infos sur tout le monde ou un channel ou une personne */
class Who: public Command {
    public:
        Who( Server * );
        ~Who( void );
        void execute( Client *, std::string );
};

/* permet de modifier le topic d'un channel ou de le visualiser */
class Topic: public Command {
    public:
        Topic( Server * );
        ~Topic( void );
        void execute( Client *, std::string );
};

#endif