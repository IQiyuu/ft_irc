#include "Command.hpp"

Part::Part( Server *serv ): Command(serv) { }
Part::~Part( void ) { }

/* bro leave le channel */
void Part::execute( Client *sender, std::string args ) {
    Channel *chan;

    if (args.empty()) {
        std::cout << "Error: " << RED << "PART need channel" << RESET << std::endl;
        sender->sendReply(NEEDMOREPARAMS_ERR(sender->getPrefix(), "PART"));
        return ;
    }
    if ((chan = this->_serv->getChannel(args.substr(0, args.find(' ') == std::string::npos ? args.size():args.find(' ')))) == NULL) {
        std::cout << "Error: " << RED << "`" << args.substr(0, args.find(' ')) << "` not found" << RESET << std::endl;
        sender->sendReply(NOSUCHCHANNEL_ERR(sender->getPrefix(), args.substr(0, args.find(' ') == std::string::npos ? args.size():args.find(' '))));
        return ;
    }
    if (!chan->isConnected(sender)) {
        std::cout << "Error: " << RED << "Not connected to `" << chan->getName() << "` not found" << RESET << std::endl;
        sender->sendReply(NOSUCHCHANNEL_ERR(sender->getPrefix(), chan->getName()));
        return ;
    }

    args.erase(0, args.find(':') == std::string::npos ? args.find(":"):args.size());
    chan->broadcast2(PART_RPL(sender->getPrefix(), chan->getName(), args));
    chan->removeMember(sender);
    //std::cout << "nb: " << chan->getMembers().size() << " - " << (chan->getMembers().empty() ? "empty":"not empty") << std::endl;
    if (chan->getMembers().empty())
        this->_serv->removeChannel(chan);
}