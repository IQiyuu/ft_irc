#include "Command.hpp"

Ping::Ping( Server *serv ): Command(serv) { }
Ping::~Ping( void ) { }

void Ping::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}