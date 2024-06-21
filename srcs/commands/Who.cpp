#include "Command.hpp"

Who::Who( Server *serv ): Command(serv) { }
Who::~Who( void ) { }

void    Who::execute( Client *sender, std::string args ) {
    (void)sender;
    (void)args;
    // /* si on envoie juste Who donner les infos sur TOUS les users */
    // if (args.empty()) {
    //     std::cout << "WHO EVERYONE" << std::endl;
    //     return ;
    // }
    
    // /* si on envoie Who #... donner les infos sur TOUS les users du channel */
    // if (args.at(0) == '#') {
    //     Channel *chan = this->_serv->getChannel(args);
    //     if (!chan) {
    //         std::cout << "Error: " << RED << "`" << args << "` channel not found" << RESET << std::endl;
    //         return ;
    //     }
    //     std::string clienList;
    //     std::vector<Client *> memb = chan->getMembers();
    //     std::vector<Client *>::iterator it;
    //     for (it = memb.begin(); it != memb.end(); ++it) {
    //         //std::cout << WHOCHAN(sender->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()) << std::endl;
    //         //std::cout << WHOCHAN(sender->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()) << std::endl;
    //         sender->sendReply(WHOCHAN(sender->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()));
    //     }
    //     //std::cout << ENDOF_WHOCHAN(sender->getNickName(), chan->getName()) << std::endl;
    //     sender->sendReply(ENDOF_WHOCHAN(sender->getNickName(), chan->getName()));
    //     return ;
    // }
    // std::cout << "WHO MEC " << args << std::endl;
}