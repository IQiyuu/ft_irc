#include "Client.hpp"

Client::Client(void) {
    std::cout << "Client: <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::Client( int fd ): _socketFd(fd), _state(NONE) {
    std::cout << "Client: <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::Client(std::string realname, std::string nickname, std::string username, int socketfd): _socketFd(socketfd), _realname(realname), _username(username), _nickname(nickname){
    std::cout << "Client: " << _nickname << GREEN << " created" << RESET << std::endl;
}

Client::~Client(void) {
    close(this->_socketFd);
    std::cout << "Client: " << _nickname << RED << " deleted" << RESET << std::endl;
}

Client &Client::operator=( const Client & ref)
{
    this->_realname = ref._realname;
    this->_username = ref._username;
    this-> _nickname = ref._nickname;
    return *this;
}

std::string Client::getNickName(void){
    return this->_nickname;
}

std::string Client::getUsername(void){
    return this->_username;
}

std::string Client::getRealname(void){
    return this->_realname;
}

int Client::getSocketFd(void){
    return this->_socketFd;
}

int Client::getState( void ) {
    return this->_state;
}

/* recupere le prefix du client sous forme de std::string */
std::string Client::getPrefix( void ) {
    std::string prefix = this->_nickname;

    prefix += (this->_username.empty() ? "" : "!") + this->_username;
    prefix += (this->_realname.empty() ? "" : "!") + this->_realname;
    prefix += " ";
    return prefix;
}

void Client::setNickName(std::string name){
    this->_nickname = name;
}

void Client::setUsername(std::string username){
    this->_username = username;
}

void Client::setRealname(std::string realname){
    this->_realname = realname;
}

void    Client::setState( int state ) {
    this->_state = state;
}

/* envoie un message au client */
void    Client::sendMsg( std::string msg ) {
    send(this->_socketFd, msg.data(), msg.size(), 0);
}

void    Client::sendReply( std::string msg ) {
    msg = ":ft_irc " + msg;
    std::cout << msg << std::endl;
    send(this->_socketFd, msg.data(), msg.size(), 0);
}