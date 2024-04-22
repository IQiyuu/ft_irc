#ifndef CHANIRC
#define CHANIRC

#include "ft_irc.hpp"

class Channel {
    private:
        /* nom du channel */
        std::string             _name;
        /* topic du channel (sujet) */
        std::string             _topic;
        /* membres du channel */
        std::vector<Client *>   _members;
        /* ops du channel (genre les modos) */
        //std::vector<Client *>   _ops;
        /* peut etre des modes */

        Channel( void );
        Channel( const Channel & );
        Channel &operator=( const Channel & );
    
    public:
        Channel( std::string );
        ~Channel( void );

        /* ajoute un membre */
        void    addMember( Client * );
        /* retire un membre */
        /* si channel vide delete le channel (a verif) */
        void    removeMember( Client * );

        /* envoie un message a tous les users */
        void    broadcast( std::string );
        /* pareil sauf pour le Client */
        void    broadcast( std::string, Client * );


        /* getters */
        std::string             getName( void );
        std::string             getTopic( void );
        std::vector<Client *>   getMembers( void );

};

#endif