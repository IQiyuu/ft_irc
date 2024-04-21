#include "Command.hpp"

PrivMsg::PrivMsg( Server *serv ): Command(serv) { }
PrivMsg::~PrivMsg( void ) { }

void PrivMsg::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}