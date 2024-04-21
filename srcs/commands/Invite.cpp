#include "Command.hpp"

Invite::Invite( Server *serv ): Command(serv) { }
Invite::~Invite( void ) { }

void Invite::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}