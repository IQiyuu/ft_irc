#include "Command.hpp"

Mode::Mode( Server *serv ): Command(serv) { }
Mode::~Mode( void ) { }

void Mode::execute( Client *sender, std::string args ) {
    if (args.empty() || args.find('+') == std::string::npos) {
        //std::cout << "Error: " << RED << "empty target." << RESET << std::endl;
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
        return ;
    }

    args = args.substr(args.find(" ") == std::string::npos ? args.size():args.find(" ")+1, args.size());
    std::cout << "|" << args << "|" << std::endl;
    if (args.empty()) {
        std::cout << "Liste des modes" << std::endl;
        return ;
    }

    if (!chan->isOp(sender)) {
        sender->sendReply(CHANOPRIVNEEDED_ERR(sender->getPrefix(), chan->getName()));
        return ;
    }
    int         state;
    std::string ret = args;
    std::string params = args.substr(args.find(' ') == std::string::npos ? args.size():args.find(' ')+1, args.size());
    if (args.at(0) == '+' || args.at(0) == '-') {
        for (int i = 0; i < (int)(args.find(' ') == std::string::npos ? args.size():args.find(' ')); i++) {
            if (args[i] == '+')
                state = 1;
            else if (args[i] == '-')
                state = 0;
            else {
                switch (args[i]) {
                    case 'i':
                        std::cout << "MODE i" << std::endl;
                        if (state == 1)
                            chan->setI(1);
                        else
                            chan->setI(0);
                        break ;
                    case 'k':
                        std::cout << "MODE k" << std::endl;
                        if (state == 1) {
                            std::string key = params.substr(0, params.find(' ') == std::string::npos ? params.size():params.find(' '));
                            chan->setK(key);
                            std::cout << key << std::endl;
                            params.erase(0, params.find(' ') == std::string::npos ? params.size():params.find(' ')+1);
                        }
                        else
                            chan->setK("");
                        break ;
                    case 't':
                        std::cout << "MODE t" << std::endl;
                        if (state == 1)
                            chan->setT(1);
                        else
                            chan->setT(0);
                        break ;
                    case 'l':
                        std::cout << "MODE l" << std::endl;
                        if (state == 1) {
                            int limit;
                            std::istringstream(params.substr(0, params.find(" ") == std::string::npos ? params.size():params.find(" "))) >> limit;
                            if (limit <= 0)
                                break ;
                            std::cout << limit << std::endl;
                            chan->setL(limit);
                            params.erase(0, params.find(' ') == std::string::npos ? params.size():params.find(' ')+1);
                        }
                        else
                            chan->setL(-1);
                        break ;
                    case 'o':
                        std::cout << "MODE o" << std::endl;
                        Client *target;
                        if ((target = this->_serv->getClient(params.substr(0, params.find(" ") == std::string::npos ? params.size():params.find(" ")))) == NULL) {
                            sender->sendReply(NOSUCHNICK_ERR(sender->getPrefix(), params.substr(0, params.find(" ") == std::string::npos ? params.size():params.find(" "))));
                            break ;
                        }
                        if (state == 1)
                            chan->addModerator(target);
                        else
                            chan->removeModerator(target);
                        std::cout << target->getNickName() << std::endl;
                        params.erase(0, params.find(' ') == std::string::npos ? params.size():params.find(' ')+1);
                    default:
                        break ;
                }
            }
        }
        chan->broadcast(MODE_RPL(chan->getName(), ret));
    }
}