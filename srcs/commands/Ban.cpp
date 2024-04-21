#include "Command.hpp"

Ban::Ban( Server *serv ): Command(serv) { }
Ban::~Ban( void ) { }

void Ban::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}