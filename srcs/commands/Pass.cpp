#include "Command.hpp"

Pass::Pass( Server *serv ): Command(serv) { }
Pass::~Pass( void ) { }

void Pass::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}