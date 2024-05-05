#include "Command.hpp"

Part::Part( Server *serv ): Command(serv) { }
Part::~Part( void ) { }

/* bro leave le channel */
void Part::execute( Client *sender, std::string args ) {
    Channel *chan;

    if (args.at(0) != '#') {
        std::cout << "Error: " << RED << "PART need channel" << RESET << std::endl;
        return ;
    }
    if (args.find(' ') == std::string::npos || args.find(':') == std::string::npos) {
        std::cout << "Error: no reason" << std::endl;
        return ;
    }
    if ((chan = this->_serv->getChannel(args.substr(0, args.find(':')))) == NULL) {
        std::cout << "Error: " << RED << "`" << args.substr(0, args.find(' ')) << "` not found" << RESET << std::endl;
        return ;
    }
    args.erase(0, args.find(':') + 1);
    chan->removeMember(sender);
    chan->broadcast(PART_RPL(sender->getNickName(), chan->getName(), args));
}