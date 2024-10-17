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
    std::vector<Client *> mod = chan->getModerator();
    std::vector<Client *>::iterator it3 = mod.begin();
    args.erase(0, args.find(' ') == std::string::npos ? args.size(): args.find(' ') + 1);
    while (it3 != mod.end()) {
        std::cout << (*it3)->getNickName() << " - " << client->getNickName() << std::endl;
        if ((*it3)->getNickName() == client->getNickName())
            break;
        ++it3;
    }

    if (it3 == mod.end())
    {
        client->sendReply(CHANOPRIVNEEDED_ERR(client->getPrefix(), chan->getName()));
        return ;
    }
    
    std::vector<Client *> modo = chan->getModerator();
    std::vector<Client *>::iterator it2 = modo.begin();
    while (it2 != modo.end()) {
        if ((*it2)->getNickName() == target->getNickName())
        {
            chan->removeModerator(*it2);
        }
        ++it2;
    }
    std::vector<Client *> mm = chan->getMembers();
    std::vector<Client *>::iterator it = mm.begin();
    while (it != mm.end()) {
        if ((*it)->getNickName() == target->getNickName())
        {
            chan->broadcast2(KICK_RPL(client->getPrefix(), target->getNickName(), chan->getName(), args));
            chan->removeMember(*it);
        }
        ++it;
    }
}