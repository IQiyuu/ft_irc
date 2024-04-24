#include "Command.hpp"

User::User( Server *serv ): Command(serv) { }
User::~User( void ) { }

void User::execute( Client *sender, std::string args ) {
    std::string uname;
    std::string realname;

    if (args.find(' ') == std::string::npos) {
        std::cout << "Error: " << RED << "pas de username" << std::endl;
        return ;
    }
    uname = args.substr(0, args.find(' '));
    if (args.find(':') == std::string::npos) {
        std::cout << "Error: " << RED << "pas de username" << std::endl;
        return ;
    }
    args.erase(0, args.find(':'));
    realname = args.substr(0, args.size());
    sender->setUsername(uname);
    sender->setRealname(realname);
    sender->welcome();
}