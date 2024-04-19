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
        Channel( const Channel * );
        operator=( const Channel * );
    
    public:
        Channel( std::string );
        ~Channel( void );

        /* ajoute un membre */
        void    addMember( Client * );
        /* retire un membre */
        void    removeMember( Client * );

        /* envoie un message a tous les users */
        void    broadcast( std::string );

};

#endif