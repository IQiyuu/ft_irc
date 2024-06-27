#include "Command.hpp"

Topic::Topic( Server *serv ): Command(serv) { }

Topic::~Topic( void ) {}

void Topic::execute(Client *sender, std::string args)
{
    Channel *chan;
    
    if (args.empty()) {
        std::cout << "Error: " << RED << "empty channel." << RESET << std::endl;
        sender->sendReply(NEEDMOREPARAMS_ERR(sender->getPrefix(), "TOPIC"));
        return ;
    }
    if (args.at(0) == '#') {
        if ((chan = this->_serv->getChannel(args.substr(0, args.find(" ") == std::string::npos ? args.size():args.find(" ")))) == NULL)  {
            sender->sendReply(NOSUCHCHANNEL_ERR(sender->getPrefix(), args.substr(0, args.find(" ") == std::string::npos ? args.size():args.find(" "))));
            return ;
        }
    }
    else
        return ;
    //retourne une erreur si le sender n'est pas  dans le channel  
    if (!chan->isConnected(sender))
        sender->sendReply(NOTONCHANNEL_ERR(sender->getPrefix(), chan->getName()));
    if (chan->getT() && !chan->isOp(sender)) {
        sender->sendReply(CHANOPRIVMSG(sender->getPrefix(), chan->getName()));
        return ;
    }
    std::string topic = args.substr(args.find(':') == std::string::npos ? 0:args.find(':') + 1, args.size());
    //std::string ch = args.substr(0, args.find(' '));
    if (!topic.empty())
        chan->setTopic(topic);
    chan->broadcast(TOPIC_RPL(sender->getPrefix(), chan->getName(), chan->getTopic()));
}

// je dois regarder si le sender est dans le channel sinon rep l erreur 442 
// si je change je dois envoyer un lessage a tout le monde du channel 
// si il est pareil  je ne fais rien 