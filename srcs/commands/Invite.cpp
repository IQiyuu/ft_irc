#include "Command.hpp"

Invite::Invite( Server *serv ): Command(serv) { }
Invite::~Invite( void ) { }

void Invite::execute( Client *client, std::string args ) {
    Client *target;
    Channel *chan;

    if (args.empty() && args.find(' ')) {
        //std::cout << "Error: " << RED "need more parameters (INVITE)" << RESET << std::endl;
        client->sendReply(NEEDMOREPARAMS_ERR(client->getPrefix(), "INVITE"));
        return ;
    }
    std::string uname = args.substr(0, args.find(' '));
    if ((target = this->_serv->getClient(uname)) != NULL) {
        args.erase(0, args.find(' ') + 1);
        if ((chan = this->_serv->getChannel(args)) != NULL) {
            if (chan->isConnected(target)) {
                client->sendReply(USERONCHANNEL_ERR(client->getPrefix(), target->getNickName(), chan->getName()));
                return ;
            }
            if (chan->isConnected(client)) {
                client->sendReply(NOTONCHANNEL_ERR(client->getPrefix(), chan->getName()));
            }
            if ((chan->getInvite() && chan->isOp(client)) || !chan->getInvite()) {
                if (!chan->isInvited(target))
                    chan->addInvited(target);
                target->sendMsg(INVITE_RPL(client->getPrefix(), uname, args));
                client->sendMsg(INVITING_RPL(client->getPrefix(), client->getNickName(), target->getNickName(), args));
                return ;
            }
            else {
                //std::cout << "Error: " << "`" << chan << "` is in invite only but `" << client->getNickName() << "` is not an operator." << std::endl;
                client->sendReply(CHANOPRIVNEEDED_ERR(client->getPrefix(), chan->getName()));
                return ;
            }
        }
        else {
            //std::cout << "Error: " << RED << "`" << args << "` Channel not found." << RESET << std::endl;
            client->sendReply(NOSUCHCHANNEL_ERR(client->getPrefix(), args));
            return ;
        }
    }
    std::cout << "Error: " << RED << "`" << uname << "` Client not found." << RESET << std::endl;
}