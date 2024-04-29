#include "Command.hpp"

Ban::Ban( Server *serv ): Command(serv) { }
Ban::~Ban( void ) { }

void Ban::execute( Client *client, std::string args ) {
    Channel *chan;
    (void)args;
    if ((chan = _serv->getChannel("#general")) == NULL) 
        chan = _serv->createChannel("#general");
    chan->addMember(client);
    std::string clientList;

    std::vector<Client *>::iterator it;
    std::vector<Client *>           memb = chan->getMembers();
    /* creer le string de la liste des users */
    for (it = memb.begin(); it != memb.end(); ++it) {
        //std::cout << WHOCHAN(sender->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()) << std::endl;
        //client->sendReply(CLIENTLIST(client->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName()));
        clientList.append((*it)->getNickName() + " ");
    }
    client->sendReply(CLIENTLIST(clientList, client->getNickName(), chan->getName()));
    client->sendReply(ENDOF_CLIENTLIST(client->getNickName(), chan->getName()));
}