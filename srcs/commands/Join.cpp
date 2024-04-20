#include "Command.hpp"

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
        for (it = chan.begin(); it != chan.end(); ++it) {
            client += it->getNickname();
            client += ' ';
        }
        client += '\n';
        send(client->getSocketFd(), welcome.data(), msg.size(), 0);
        send(client->getSocketFd(), cl.data(), msg.size(), 0);
        send(client->getSocketFd(), msg.data(), msg.size(), 0);
        _serv->_channels->addMember(client);
    }
}