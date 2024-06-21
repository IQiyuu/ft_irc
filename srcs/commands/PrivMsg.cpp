#include "Command.hpp"

PrivMsg::PrivMsg( Server *serv ): Command(serv) { }
PrivMsg::~PrivMsg( void ) { }

/* messages prives */
void PrivMsg::execute( Client *client, std::string args ) {
    std::string receiverNname;

    /* faire un truc si il n'y a pas de cible  */
    if (!args.empty()) {
        if (args.find(' ') != std::string::npos) {
            receiverNname = args.substr(0, args.find(' '));
            args = args.substr(args.find(' ') + 1, args.size());
        }
    }
    else {
        std::cout << "Error: " << RED << "empty target" << RESET << std::endl;
        client->sendReply(NOSUCHNICK_ERR(client->getPrefix(), ""));
        return ;
    }
    /* faire un truc si le message est vide */
    if (args.empty()) {
        std::cout << "Error: " << RED << "empty message" << RESET << std::endl;
        client->sendReply(NOTEXTTOSEND_ERR(client->getPrefix()));
        return ;
    }
    /* on enleve les : */
    if (args.at(0) == ':')
        args.substr(1);

    /* on envoie a un chan */
    if (receiverNname.at(0) == '#') {
        Channel *chan = this->_serv->getChannel(receiverNname);
        /* faire un truc si le chan n'existe pas */
        if (chan == NULL) {
            client->sendReply(NOSUCHNICK_ERR(client->getPrefix(), chan->getName()));
            return ;
        }
        /* si le client est dans le chan broadcast */
        std::vector<Client *> memb = chan->getMembers();
        std::vector<Client *>::iterator it = memb.begin();
        while (it != memb.end()) {
            if ((*it)->getNickName() == client->getNickName()) {
                chan->broadcast(PRIVMSG_RPL(client->getNickName(), receiverNname, args), client);
                return ;
            }
            it++;
        }
        /* si le client n'est pas dans le serv faire un truc */        
        return ;
    }

    /* on envoie a un client */
    Client  *cible = this->_serv->getClient(receiverNname);
    /* faire un truc si la cible n'existe pas */
    if (cible == NULL) {
        std::cout << "Error: " << RED << "`" << receiverNname << "` Unknow client" << RESET << std::endl;
        client->sendReply(NOSUCHNICK_ERR(client->getPrefix(), receiverNname));
        return ;
    }
    cible->sendMsg(PRIVMSG_RPL(client->getNickName(), receiverNname, args));
}