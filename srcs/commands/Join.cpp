#include "Command.hpp"

Join::Join( Server *serv ): Command(serv) { }
Join::~Join( void ) { }

/* le client rejoind un channel ou le creer si il n'existe pas*/
void Join::execute(Client *client, std::string args)
{
    Channel *chan;

    /* faire un truc si args est vide */
    if (args.empty()) {
        std::cout << "Error: " << RED << "empty channel." << RESET << std::endl;
        client->sendReply(NEEDMOREPARAMS_ERR(client->getPrefix(), "JOIN"));
        return ;
    }
    /* creer le channel si il n'existe pas */
    if ((chan = this->_serv->getChannel(args)) == NULL)  {
        chan = this->_serv->createChannel(args);
    }
    else if (chan->isConnected(client)){
        return ;
    }
    /* si le channel est en invite only verifier que le client est invite */
    else if (chan->getInvite()) {
        /* si le channel a une key verfier que le client a la bonne */
        if (!chan->getKey().empty()) {
            if (args.find(' ') == std::string::npos) {
                client->sendReply(BADKEYCHANNEL_ERR(client->getPrefix(), chan->getName()));
                return ;
            }
            std::string key = args.substr(args.find(' ') + 1, args.size());
            if (key.compare(chan->getKey()))
                client->sendReply(BADKEYCHANNEL_ERR(client->getPrefix(), chan->getName()));
        }
    }
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
    client->sendReply(CLIENTLIST(clientList, client->getPrefix(), chan->getName()));
    client->sendReply(ENDOF_CLIENTLIST(client->getPrefix(), chan->getName()));

    std::cout << "(" << chan->getName() << ")" << std::endl;
    
    /* on envoie les reponses au client */
    // client->sendMsg(WHOCHAN(client->getPrefix(), clientList, client->getNickName(), chan->getName()));
    // client->sendMsg(ENDOF_CLIENTLIST(client->getPrefix(), client->getNickName(), chan->getName()));
    /* ajoute le nouveau client au channel */
    
}