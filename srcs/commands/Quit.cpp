#include "Command.hpp"

Quit::Quit( Server *serv ): Command(serv) { }
Quit::~Quit( void ) { }

/* bro veut partir */
void Quit::execute( Client *sender, std::string args ) {
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    /* faut le deco de tous les channels pour enlever le segfault  */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    sender->sendReply(QUIT_RPL(sender->getNickName(), args));
    /* broadcast a tous les channels ou il etait co qu'il se deco */
    this->_serv->sendToConnected(sender, QUIT_RPL(sender->getNickName(), args));
    this->_serv->disconnect(sender->getSocketFd());
}