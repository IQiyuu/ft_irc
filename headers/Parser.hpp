#ifndef PARSERIRC
#define PARSERIRC

#include "ft_irc.hpp"

class Parser {
    private:
        std::map<std::string, Command *> _commands;
        Parser( void );
        Parser( const Parser & );
        Parser &operator=( const Parser & );

    public:
        Parser( Server * );
        ~Parser( void );

        /************************************/
        /*            -_('o')_-             */
        /************************************/
        void parse( Client *, std::string );
};

#endif