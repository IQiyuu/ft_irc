#include "Command.hpp"

Join::Join( Server *serv ): Command(serv) { }
Join::~Join( void ) { }

/* le client rejoind un channel ou le creer si il n'existe pas*/
void Join::execute(Client *client, std::string args)
{
    Channel *chan;

    /* faire un truc si args est vide */
    if (args.empty())
        return ;
    /* creer le channel si il n'existe pas */
    if ((chan = _serv->getChannel(args)) == NULL) 
        chan = _serv->createChannel(args);
    chan->addMember(client);
    chan->addModerator(client);
    std::string clientList;

    std::vector<Client *>::iterator it;
    std::vector<Client *>           memb = chan->getMembers();
    /* creer le string de la liste des users */
    for (it = memb.begin(); it != memb.end(); ++it) {
        //std::cout << WHOCHAN(sender->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()) << std::endl;
        //client->sendReply(CLIENTLIST(client->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName()));
        clientList.append((*it)->getNickName() + " ");
    }
    chan->broadcast(JOIN_RPL(client->getPrefix(), chan->getName()));
    client->sendReply(CLIENTLIST(clientList, client->getNickName(), chan->getName()));
    client->sendReply(ENDOF_CLIENTLIST(client->getNickName(), chan->getName()));

    std::cout << "(" << chan->getName() << ")" << std::endl;
    
    /* on envoie les reponses au client */
    // client->sendMsg(WHOCHAN(client->getPrefix(), clientList, client->getNickName(), chan->getName()));
    // client->sendMsg(ENDOF_CLIENTLIST(client->getPrefix(), client->getNickName(), chan->getName()));
    /* ajoute le nouveau client au channel */
    
}