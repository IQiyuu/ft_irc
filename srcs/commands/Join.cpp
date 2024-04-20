#include "Command.hpp"

void Join::execute(Client *client, std::string args)
{ 
   if (_serv->channelExist(args) == NULL)
   {
        _serv->newChannel(args);
   }
   else
   {
        _serv->_channels->addMember(client);
   }
}