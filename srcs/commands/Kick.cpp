#include "Command.hpp"

Kick::Kick( Server *serv ): Command(serv) { }
Kick::~Kick( void ) { }
// manque a regarder si on le fait dans un channel 
void Kick::execute( Client *client, std::string args ) {
    (void)args;
    (void)client;
    if (args.at(0) != '#') {
        std::cout << "Error: " << RED << " KICK need channel" << RESET << std::endl;
        return ;
    }
    if (args.find(' ') == std::string::npos)
    {

        //display error  pas d'espace trouvé 
    }
    Channel *chan = _serv->getChannel(args.substr(0, args.find(' ')));
    args.erase(0, args.find(' ') + 1);
    std::vector<Client *> modo = chan->getMembers();
    std::vector<Client *>::iterator it2 = modo.begin();
    while (it2 != modo.end()) {
        if ((*it2)->getNickName() != client->getNickName())
            chan->removeMember(*it2);
        ++it2;
    }
    std::vector<Client *> mm = chan->getMembers();
    std::vector<Client *>::iterator it = mm.begin();
    while (it != mm.end()) {
        //std::vector<Client *> mm = (*it)->getNickName();
        if ((*it)->getNickName() != args)
            chan->removeMember(*it);
        ++it;
    }
    
}