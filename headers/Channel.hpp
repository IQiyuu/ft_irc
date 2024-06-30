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
        std::vector<Client *>   _ops;
        /* invited to the channel */
        std::vector<Client *>   _invited;

        /* peut etre des modes */
        int                     _l;
        std::string             _k;
        int                    _t;
        int                    _i;

        Channel( void );
        Channel( const Channel & );
        Channel &operator=( const Channel & );
    
    public:
        Channel( std::string );
        ~Channel( void );

        /* ajoute un membre */
        void    addMember( Client * );

        void    addInvited( Client * );

        void    addModerator( Client * );
        /* retire un membre */
        /* si channel vide delete le channel (a verif) */
        void    removeMember( Client * );

        void    removeModerator( Client * );

        void    removeInvited( Client * );

        /* verifie si le client est connecte au channel */
        int     isConnected( Client * );

        /* verifie si le client donne est operator */
        int     isOp( Client * );

        /* verifie si le client est invite sur le channel*/
        int    isInvited( Client * );

        /* envoie un message a tous les users */
        void    broadcast( std::string );
        /* pareil sauf pour le Client */
        void    broadcast( std::string, Client * );

        void    broadcast2( std::string );


        /* getters */
        std::string             getName( void );
        std::string             getTopic( void );
        std::vector<Client *>   getMembers( void );
        std::vector<Client *>   getModerator( void );
        int                     getLimit( void );

        void                    setI( int );
        void                    setT( int );
        void                    setL( int );
        void                    setK( std::string );

        void                    setTopic( std::string );

        int                     getInvite( void );
        std::string             getKey( void );
        int                     getT( void );

};

#endif