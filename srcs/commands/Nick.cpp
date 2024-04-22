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
    //     if (isalpha(args[i]) || isalnum(args[i]) || args[i] == '_' || args[i] == '-' || args[i] == ' ')
    //     {
    //         std::cout << "Error: " << RED << + "`" << args[i] << "`Incorrect character." << RESET << std::endl;
    //         return;
    //     }
    // }
    client->setNickName(args);
    client->sendReply(WELCOME_RPL(client->getNickName()));
    /* faire un broadcast sur tous les channels presents pour dire qu'il a swap de nickname */
    return;
}