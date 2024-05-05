#include "Command.hpp"

Invite::Invite( Server *serv ): Command(serv) { }
Invite::~Invite( void ) { }

void Invite::execute( Client *client, std::string args ) {
    Client *target;

    if (args.empty()) {
        std::cout << "Error: " << RED "No client input" << RESET << std::endl;
        return ;
    }

    if (args.find(' ') == std::string::npos) {
        std::cout << "Error: " << RED << "No channel input" << RESET << std::endl;
        return ;
    }
    std::string uname = args.substr(0, args.find(' '));
    if ((target = this->_serv->getClient(uname)) != NULL) {
        args.erase(0, args.find(' ') + 1);
        target->sendMsg(INVITE_RPL(client->getNickName(), uname, args));
        return ;    
    }
    std::cout << "Error: " << RED << "`" << uname << "` Client not found" << RESET << std::endl;
}