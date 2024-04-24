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
   // std::string clientList;

    // std::vector<Client *>::iterator it;
    // std::vector<Client *>           memb = chan->getMembers();
    // /* creer le string de la liste des users */
    // for (it = memb.begin(); it != memb.end(); ++it) {
    //     //std::cout << WHOCHAN(sender->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()) << std::endl;
    //     client->sendReply(WHOCHAN(client->getNickName(), chan->getName(), (*it)->getNickName(), (*it)->getHostName(), (*it)->getUsername()));
    // }
    // client->sendReply(ENDOF_WHOCHAN(client->getNickName(), chan->getName()));

    //std::cout << "(" << client->getNickName() << ")" << std::endl;
    /* on envoie les reponses au client */
    // client->sendMsg(WHOCHAN(client->getPrefix(), clientList, client->getNickName(), chan->getName()));
    // client->sendMsg(ENDOF_CLIENTLIST(client->getPrefix(), client->getNickName(), chan->getName()));
    /* ajoute le nouveau client au channel */
    chan->broadcast(JOIN_RPL(client->getPrefix(), chan->getName()));
}