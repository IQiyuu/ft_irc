#include "Command.hpp"

Kick::Kick( Server *serv ): Command(serv) { }
Kick::~Kick( void ) { }
// manque a regarder si on le fait dans un channel 
void Kick::execute( Client *client, std::string args ) {
    Channel *chan;
    Client  *target;
    if (args.at(0) != '#' || args.find(' ') == std::string::npos) {
        client->sendReply(NEEDMOREPARAMS_ERR(client->getPrefix(), "KICK"));
        return ;
    }
    if ((chan = _serv->getChannel(args.substr(0, args.find(' ')))) == NULL) {
        client->sendReply(NOSUCHCHANNEL_ERR(client->getPrefix(), args.substr(0, args.find(' '))));
        return ;
    }
    args.erase(0, args.find(' ') + 1);
    std::cout << args.substr(0, args.find(' ') == std::string::npos ? args.size(): args.find(' ')) << std::endl;
    if ((target = this->_serv->getClient(args.substr(0, args.find(' ') == std::string::npos ? args.size(): args.find(' ')))) == NULL) {
        client->sendReply(NOSUCHNICK_ERR(client->getPrefix(), args.substr(0, args.find(' ') == std::string::npos ? args.size(): args.find(' '))));
        return ;
    }
    if (!chan->isConnected(client)) {
        client->sendReply(NOTONCHANNEL_ERR(client->getPrefix(), chan->getName()));
        return ;
    }
    if (!chan->isConnected(target)) {
        client->sendReply(NOTINCHANNEL_ERR(client->getPrefix(), target->getNickName(), chan->getName()));
        return ;
    }
    args.erase(0, args.find(' ') == std::string::npos ? args.size(): args.find(' ') + 1);
    chan->broadcast2(KICK_RPL(client->getPrefix(), target->getNickName(), chan->getName(), args));
    std::vector<Client *> modo = chan->getModerator();
    std::vector<Client *>::iterator it2 = modo.begin();
    while (it2 != modo.end()) {
        if ((*it2)->getNickName() == target->getNickName())
            chan->removeModerator(*it2);
        ++it2;
    }
    std::vector<Client *> mm = chan->getMembers();
    std::vector<Client *>::iterator it = mm.begin();
    while (it != mm.end()) {
        //std::vector<Client *> mm = (*it)->getNickName();
        if ((*it)->getNickName() == target->getNickName())
            chan->removeMember(*it);
        ++it;
    }
}