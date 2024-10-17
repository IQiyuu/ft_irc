#include "Command.hpp"

Nick::Nick( Server *serv ): Command(serv) { }
Nick::~Nick( void ) { }

/* change le nickname du client */
// ajouter un check pour voir si le pseudo exite deja et voir si c'est pas un nom de commande
void Nick::execute(Client *client, std::string args)
{
   
    if (client->getState() == BADPASS || client->getState() == NONE)
        return ;
    if (args.size()  > 12)
    {
        std::cout << "Error: " << RED << "nickname too long" << RESET << std::endl;
        return;
    }
    for (int i = 0; i <= (int)args.size() - 1; i++)
    {
        if ((!isalnum(args[i]) && args[i] != '_'))
        {
            client->sendReply(NICKNAMERRONEUS_ERR(client->getPrefix(), args));
            return;
        }
        if (i == 0 && args[i] >= '0' && args[i] <= '9')
        {
            client->sendReply(NICKNAMERRONEUS_ERR(client->getPrefix(), args));
            return;
        }
    }
    if (this->_serv->getClient(args) != NULL) {
        client->setNickName(args);
        std::string tmp = client->getPrefix();
        std::cout << "Error: " << RED << "`" << args << "` nickname already used" << RESET << std::endl;
        client->sendReply(NICKNAMEINUSE_ERR(client->getNickName(), args));
        client->sendMsg(NICK_RPL(tmp, client->getNickName()));
        return ;
    }
    std::string tmp = client->getPrefix();
    if (client->getState() != LOGED) {
        client->setNickName(args);
        if (client->getState() == REGISTERED) {
            client->welcome();
            return ;
        }
        if (client->getState() == AUTH) {
            client->setState(REGISTERED);
            return ;
        }
    }
    client->sendMsg(NICK_RPL(tmp, args));
    //client->welcome();
    /* faire un broadcast sur tous les channels presents pour dire qu'il a swap de nickname */
    this->_serv->sendToConnected(client, NICK_RPL(tmp, args));
    client->setNickName(args);
    return;
}