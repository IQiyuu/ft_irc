#include "Command.hpp"

Mode::Mode( Server *serv ): Command(serv) { }
Mode::~Mode( void ) { }

void Mode::execute( Client *sender, std::string args ) {
    if (args.find("+") == std::string::npos) {
        sender->sendReply("324 dgoubin #general");
        return ;
    }
    args = args.substr(args.find("+"), args.find("\r"));
    sender->sendReply(MODE_RPL(sender->getNickName(), args));
}