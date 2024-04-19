#include "Command.hpp"


// ajouter un check pour voir si le pseudo exite deja et voir si c'est pas un nom de commande
int Nick(Client *client, std::string args)
{
    if (args.size()  > 12)
    {
        std::cout << "Error: " << RED << "nickname too long" << RESET << std::endl;
        return ERROR;
    }
    for (int i = 0; i <= args.size(); i++)
    {
        if (!isalpha(args[i]) && !isalnum(args[i]) && args[i] != '_' && args[i] != '-' && args[i] != ' ')
        {
            std::cout << "Error: " << RED << "incorrect character." << RESET << std::endl;
            return ERROR;
        }
    }
    client->setNickName(args);
    return SUCCESS;
}