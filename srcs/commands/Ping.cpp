#include "Command.hpp"

Ping::Ping( Server *serv ): Command(serv) { }
Ping::~Ping( void ) { }

void Ping::execute( Client *sender, std::string args ) {
    sender->sendMsg(PING_RPL(sender->getNickName(), args));
}