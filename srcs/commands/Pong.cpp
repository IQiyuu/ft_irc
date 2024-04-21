#include "Command.hpp"

Pong::Pong( Server *serv ): Command(serv) { }
Pong::~Pong( void ) { }

void Pong::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}