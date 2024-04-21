#include "Command.hpp"

User::User( Server *serv ): Command(serv) { }
User::~User( void ) { }

void User::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}