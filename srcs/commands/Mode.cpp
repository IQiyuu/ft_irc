#include "Command.hpp"

Mode::Mode( Server *serv ): Command(serv) { }
Mode::~Mode( void ) { }

void Mode::execute( Client *client, std::string args ) {
    (void) client;
    (void) args;
}