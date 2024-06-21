#include "Command.hpp"

Cap::Cap( Server *serv ): Command(serv) { }
Cap::~Cap( void ) { }

/* renvoie les capacites du serv (:none mdr) mais hexchat le demande */
void Cap::execute( Client *sender, std::string args ) {
    (void)sender;
    (void)args;
}