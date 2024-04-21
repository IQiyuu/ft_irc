#include "Command.hpp"

Join::Join( Server *serv ): Command(serv) { }
Join::~Join( void ) { }

void Join::execute(Client *client, std::string args)
{
    Channel *chan;
    std::string msg = "#";
    msg += args;
    msg += " : End of username list.\n";
    std::string cl = "#";
    cl += args;
    cl += " :";
    std::string welcome = "#";
    welcome += args;
    welcome += " :Welcome to ";
    welcome += args;
    welcome += '\n';
    std::string empty = "#";
    empty += args;
    empty += ":This channel is empty.";
    std::string nw = "#";
    nw += args;
    nw += " :";
    nw += client->getNickName();
    if ((chan = _serv->channelExist(args)) == NULL)
    {
        send(client->getSocketFd(), empty.data(), msg.size(), 0);
        send(client->getSocketFd(), nw.data(), msg.size(), 0);
        send(client->getSocketFd(), msg.data(), msg.size(), 0);
        _serv->newChannel(args);
    }
    else
    {
        std::vector<Client *>::iterator it;
        std::vector<Client *>           memb;
        for (it = memb.begin(); it != memb.end(); ++it) {
            cl += (*it)->getNickName();
            cl += ' ';
        }
        client += '\n';
        send(client->getSocketFd(), welcome.data(), msg.size(), 0);
        send(client->getSocketFd(), cl.data(), msg.size(), 0);
        send(client->getSocketFd(), msg.data(), msg.size(), 0);
        chan->addMember(client);
    }
}