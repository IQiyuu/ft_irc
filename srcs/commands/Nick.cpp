#include "Command.hpp"

Nick::Nick( Server *serv ): Command(serv) { }
Nick::~Nick( void ) { }

/* change le nickname du client */
// ajouter un check pour voir si le pseudo exite deja et voir si c'est pas un nom de commande
void Nick::execute(Client *client, std::string args)
{
    if (args.size()  > 12)
    {
        std::cout << "Error: " << RED << "nickname too long" << RESET << std::endl;
        return;
    }
    // for (int i = 0; i <= (int)args.size(); i++)
    // {
    //     if (!isalpha(args[i]) || !isalnum(args[i]))
    //     {
    //         std::cout << "Error: " << RED << + "`" << args[i] << "` incorrect character." << RESET << std::endl;
    //         return;
    //     }
    // }
    std::string tmp = client->getNickName();
    if (this->_serv->getClient(args) != NULL) {
        std::cout << "Error: " << RED << "`" << args << "` already connected" << RESET << std::endl;
        if (client->getUsername().empty()) {
            std::string nname = "client";
            std::stringstream ss;
            ss << std::rand()%100;
            nname += ss.str();
            client->setNickName(nname);
        }
        return ;
    }
    client->setNickName(args);
    /* faire un broadcast sur tous les channels presents pour dire qu'il a swap de nickname */
    this->_serv->sendToConnected(client, NICK_RPL(tmp, client->getNickName()));
    return;
}