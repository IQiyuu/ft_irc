#include "Command.hpp"

Pass::Pass( Server *serv ): Command(serv) { }
Pass::~Pass( void ) { }

/* s'identifier au serv */
void Pass::execute( Client *client, std::string args ) {
    /* faire quelque chose si args est vide */
    if (args.empty())
        return ;
    client->setState(LOGED);
}