#include "Command.hpp"

Pass::Pass( Server *serv ): Command(serv) { }
Pass::~Pass( void ) { }

/* s'identifier au serv */
void Pass::execute( Client *sender, std::string args ) {
    /* faire quelque chose si args est vide */
    if (args.empty()) {
        std::cout << "Error: " << RED << "empty pass." << RESET << std::endl;
        sender->sendReply(NEEDMOREPARAMS_ERR(sender->getPrefix(), "PASS"));
        return ;
    }
    if (this->_serv->getPass().compare(args)) {
        std::cout << "Error: " << RED << "bad password." << RESET << "(" << this->_serv->getPass() << "-" << args << ")" << std::endl;
        sender->sendReply(PASSMISMATCH_ERR(sender->getPrefix()));
        sender->setState(BADPASS);
        return ;
    }
    sender->setState(AUTH);
}