#include "Channel.hpp"

Channel::Channel(std::string name, Client *client ):_name(name) {
    std::cout << "Channel: " << _name << GREEN << " created." << RESET << std::endl;
    _members.push_back(client);
}
Channel::~Channel(void){
    std::cout << "Channel: " << _name << RED << " deleted." << RESET << std::endl;
}

Channel &Channel::operator=(const Channel &ref)
{
    this->_name = ref._name;
    this->_topic = ref._topic;
    return *this;
}

void Channel::addMember(Client *client)
{
    _members.push_back(client);
}

void Channel::removeMember(Client *client)
{
    std::vector<Client*>::iterator it;
    for (it = _members.begin(); it != _members.end(); it++)
    {
        if (*it == client)
        {
            _members.erase(it);
            return ;
        }
    }
    std::cout << "No members named " << client->getNickName() << " in " << _name << "." << std::endl;
}

std::string Channel::getName( void ) {
    return this->_name;
}

std::string Channel::getTopic( void ) {
    return this->_topic;
}

std::vector<Client *>   Channel::getMembers( void ) {
    return this->_members;
}

void    Channel::broadcast( std::string msg ) {
    std::vector<Client *>::iterator it;

    for (it = this->_members.begin(); it != this->_members.end(); ++it)
        (*it)->sendMsg(msg);
}