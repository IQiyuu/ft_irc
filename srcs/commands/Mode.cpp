#include "Command.hpp"

Mode::Mode( Server *serv ): Command(serv) { }
Mode::~Mode( void ) { }

void Mode::execute( Client *sender, std::string args ) {
    if (args.empty()) {
        std::cout << "Error: " << RED << "empty target." << RESET << std::endl;
        sender->sendReply(NEEDMOREPARAMS_ERR(sender->getPrefix(), "MODE"));
        return ;
    }
    // on recupere le channel ou a ete execute la commande
    Channel *chan;
    if (args.at(0) == '#') {
        if ((chan = this->_serv->getChannel(args.substr(0, (args.find(" ") == std::string::npos ? args.size():args.find(" "))))) == NULL)  {
            sender->sendReply(NOSUCHCHANNEL_ERR(sender->getPrefix(), args.substr(0, (args.find(" ") == std::string::npos ? args.size():args.find(" ")))));
            return ;
        }
    }
    else {
        args = args.substr(args.find("+"), args.find("\r"));
        sender->sendReply(MODE_RPL(sender->getNickName(), args));
    }

    args = args.substr(args.find(" ") == std::string::npos ? args.size():args.find(" ")+1, args.size());
    std::cout << "|" << args << "|" << std::endl;
    if (args.empty()) {
        std::cout << "Liste des modes" << std::endl;
        return ;
    }

    if (!chan->isOp(sender)) {
        sender->sendReply(CHANOPRIVMSG(sender->getPrefix(), chan->getName()));
        return ;
    }
    if (args.at(0) == '+' || args.at(0) == '-') {
        switch (args.at(1)) {
            case 'i':
                std::cout << "MODE +i" << std::endl;
                if (args.at(0) == '+')
                    chan->setI(false);
                else
                    chan->setI(true);
                chan->broadcast(MODE_RPL(chan->getName(), args));
                break ;
            case 'k':
                std::cout << "MODE +k with " << args.substr(2, args.size()) << std::endl;
                if (args.at(0) == '+')
                    chan->setK(args.substr(args.find(" ") == std::string::npos ? args.size():args.find(" ")+1, args.size()));
                else
                    chan->setK("");
                std::cout << "BROADCAST BEFORE" << std::endl;
                chan->broadcast(MODE_RPL(chan->getName(), args));
                std::cout << "BROADCAST PASSED" << std::endl;
                break ;
            case 't':
                std::cout << "MODE +t" << std::endl;
                if (args.at(0) == '+')
                    chan->setT(false);
                else
                    chan->setT(true);
                chan->broadcast(MODE_RPL(chan->getName(), args));
                break ;
            case 'l':
                std::cout << "MODE +l to " << args.substr(2, args.size()) << std::endl;
                if (args.at(0) == '+') {
                    int limit;
                    std::istringstream(args.substr(args.find(" ") == std::string::npos ? args.size():args.find(" ")+1, args.size())) >> limit;
                    if (limit <= 0)
                        return ;
                    chan->setL(limit);
                }
                else
                    chan->setL(-1);
                chan->broadcast(MODE_RPL(chan->getName(), args));
                break ;
            default:
                Client *target;
                if ((target = this->_serv->getClient(args.substr(args.find(" ") == std::string::npos ? args.size():args.find(" ")+1, args.size()))) == NULL) {
                    std::cout << "Client doesn't exist." << std::endl;
                    return ;
                }
                if (args.at(0) == '+')
                    chan->addModerator(target);
                else
                    chan->removeModerator(target);
                chan->broadcast(MODE_RPL(chan->getName(), args));
        }
    }
}