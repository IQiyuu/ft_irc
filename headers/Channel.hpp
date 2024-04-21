#ifndef CHANIRC
#define CHANIRC

#include "ft_irc.hpp"

class Channel {
    private:
        std::string             _name;
        std::string             _topic;
        std::vector<Client *>   _members;
        //std::vector<Client *>   _ops;

        Channel( void );
        Channel( const Channel & );
        Channel &operator=( const Channel & );
    
    public:
        Channel( std::string, Client * );
        ~Channel( void );

        /* ajoute un membre */
        void    addMember( Client * );
        /* retire un membre */
        //si channel vide delete le channel
        void    removeMember( Client * );

        /* envoie un message a tous les users */
        void    broadcast( std::string );

        /* getters */
        std::string getName( void );
        std::string getTopic( void );
        std::vector<Client *>   getMembers( void );

};

#endif