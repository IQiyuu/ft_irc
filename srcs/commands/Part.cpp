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
    if ((chan = this->_serv->getChannel(args.substr(0, args.find(' ') == std::string::npos ? args.size():args.find(' ')))) == NULL) {
        std::cout << "Error: " << RED << "`" << args.substr(0, args.find(' ')) << "` not found" << RESET << std::endl;
        return ;
    }
    if (args.find(' ') == std::string::npos || args.find(':') == std::string::npos) {
        chan->broadcast(PART_RPL(sender->getPrefix(), chan->getName(), ""));
        chan->removeMember(sender);
        return ;
    }
    args.erase(0, args.find(':'));
    chan->broadcast(PART_RPL(sender->getPrefix(), chan->getName(), args));
    chan->removeMember(sender);
}