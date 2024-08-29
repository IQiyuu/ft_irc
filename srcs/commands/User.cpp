#include "Command.hpp"

User::User( Server *serv ): Command(serv) { }
User::~User( void ) { }

void User::execute( Client *sender, std::string args ) {
    std::string uname;
    std::string realname;

    if (sender->getState() == BADPASS || sender->getState() == NONE)
        return ;
    if (sender->getState() == LOGED) {
        std::cout << "Error: " << RED << "USER already connected." << RESET << std::endl;
        sender->sendReply(ALREADYREGISTERED_ERR(sender->getPrefix()));
        return ;
    }
    if (args.empty() || args.find(' ') == std::string::npos) {
        std::cout << "Error: " << RED << "USER no username" << RESET << std::endl;
        sender->sendReply(NEEDMOREPARAMS_ERR(sender->getPrefix(), "USER"));
        return ;
    }
    uname = args.substr(0, args.find(' '));
    if (args.find(':') == std::string::npos) {
        std::cout << "Error: " << RED << "USER no realname" << RESET << std::endl;
        sender->sendReply(NEEDMOREPARAMS_ERR(sender->getPrefix(), "USER"));
        return ;
    }
    args.erase(0, args.find(':'));
    realname = args.substr(0, args.size());
    sender->setUsername(uname);
    sender->setRealname(realname);
    if (sender->getState() == AUTH)
        sender->setState(REGISTERED);
    else if (sender->getState() == REGISTERED) {
        sender->welcome();
    }
}