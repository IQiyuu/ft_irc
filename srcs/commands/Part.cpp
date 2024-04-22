#include "Command.hpp"

Part::Part( Server *serv ): Command(serv) { }
Part::~Part( void ) { }

/* bro leave le channel */
void Part::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}