#include "Command.hpp"

Kick::Kick( Server *serv ): Command(serv) { }
Kick::~Kick( void ) { }

void Kick::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}