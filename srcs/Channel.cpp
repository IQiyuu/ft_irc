#include "Channel.hpp"

Channel::Channel(std::string name ):_name(name) {
    std::cout << "Channel: " << _name << GREEN << " created." << RESET << std::endl;
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

/* ajoute un client aux membres du channel */
void Channel::addMember(Client *client)
{
    _members.push_back(client);
}

/* ajoute un client aux moderateurs du channel */
void Channel::addModerator(Client *client)
{
    _ops.push_back(client);
}

/* retourne 1 si client est op 0 sinon */
int Channel::isOp( Client *client ) {
    std::vector<Client *>::iterator it;
    std::vector<Client *>           op = this->_ops;
    for (it = op.begin(); it != op.end(); ++it) 
        if (*it == client)
            return 1;
    return 0;
}

/* supprime le client des membres du channel */
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

void Channel::removeModerator(Client *client)
{
    std::vector<Client*>::iterator it;
    for (it = _ops.begin(); it != _ops.end(); it++)
    {
        if (*it == client)
        {
            _ops.erase(it);
            return ;
        }
    }
    std::cout << "No members named " << client->getNickName() << " in " << _name << "." << std::endl;
}

/* renvoie 1 si client est connected 0 sinon */
int Channel::isConnected(Client *client) {
    std::vector<Client*>::iterator it;

    for (it = _members.begin(); it != _members.end(); it++)
        if (*it == client)
            return 1;
    return 0;
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

std::vector<Client *>   Channel::getModerator( void ) {
    return this->_ops;
}

bool                    Channel::getInvite( void ) {
    return this->_i;
}

std::string             Channel::getKey( void ) {
    return this->_k;
}

int                     Channel::getLimit( void ) {
    return this->_l;
}

void    Channel::setK( std::string key ) {
    this->_k = key;
}

void    Channel::setL( int limit ) {
    this->_l = limit;
}

void    Channel::setT( bool t ) {
    this->_t = t;
}

void    Channel::setI( bool i ) {
    this->_i = i;
}

/* envoie un message a tous les membres du channel */
void    Channel::broadcast( std::string msg ) {
    std::vector<Client *>::iterator it;

    for (it = this->_members.begin(); it != this->_members.end(); ++it) {
        (*it)->sendReply(msg);
    }
}

void    Channel::broadcast2( std::string msg ) {
    std::vector<Client *>::iterator it;

    for (it = this->_members.begin(); it != this->_members.end(); ++it) {
        (*it)->sendMsg(msg);
    }
}
/* envoie un message a tous les membres du channel sauf a notHim */
void    Channel::broadcast( std::string msg, Client *notHim ) {
    std::vector<Client *>::iterator it;

    for (it = this->_members.begin(); it != this->_members.end(); ++it) {
        if ((*it)->getNickName().compare(notHim->getNickName()))
            (*it)->sendMsg(msg);
    }
}