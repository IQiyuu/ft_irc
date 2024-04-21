#include "Command.hpp"

Join::Join( Server *serv ): Command(serv) { }
Join::~Join( void ) { }

void Join::execute(Client *client, std::string args)
{
    Channel *chan;

    /* faire un truc si args est vide */
    if (args.empty())
        return ;
    /* creer le channel si il n'existe pas */
    if ((chan = _serv->getChannel(args)) == NULL)
        chan = _serv->createChannel(args, client);
    std::string clientList = client->getNickName() + ' ';

    std::vector<Client *>::iterator it;
    std::vector<Client *>           memb;
    /* creer le string de la liste des users */
    for (it = memb.begin(); it != memb.end(); ++it)
        clientList += (*it)->getNickName() + ' ';
    
    std::cout << "(" << client->getNickName() << ")" << std::endl;
    /* on envoie les reponses au client */
    client->sendReply(NO_TOPIC(client->getNickName(), chan->getName()));
    client->sendReply(CLIENTLIST(clientList, client->getNickName(), chan->getName()));
    client->sendReply(ENDOF_CLIENTLIST(client->getNickName(), chan->getName()));
    /* ajoute le nouveau client au channel */
    chan->addMember(client);
    //chan->broadcast(JOIN_RPL(client->getPrefix(), chan->getName()));
}