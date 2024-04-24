#include "Command.hpp"

Pass::Pass( Server *serv ): Command(serv) { }
Pass::~Pass( void ) { }

/* s'identifier au serv */
void Pass::execute( Client *sender, std::string args ) {

    if (sender->getState() != NONE) {
        std::cout << "Error: " << RED << "already connected" << RESET << std::endl;
        return ;
    }
    /* faire quelque chose si args est vide */
    if (args.empty()) {
        std::cout << "Error: " << RED << "empty pass" << RESET << std::endl;
        return ;
    }
    if (this->_serv->getPass().compare(args)) {
        std::cout << "Error: " << RED << "bad password" << RESET << std::endl;
        return ;
    }
    sender->setState(AUTH);
}