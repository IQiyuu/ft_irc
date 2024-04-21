#include "Client.hpp"

Client::Client(void) {
    std::cout << "Client : <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::Client( int fd ): _socketFd(fd) {
    std::cout << "Client : <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::Client(std::string realname, std::string nickname, std::string username, int socketfd): _socketFd(socketfd), _realname(realname), _username(username), _nickname(nickname){
    std::cout << "Client :" << _nickname << GREEN << " created" << RESET << std::endl;
}

Client::~Client(void) {
    std::cout << "Client :" << _nickname << RED << " deleted" << RESET << std::endl;
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

void Client::setNickName(std::string name){
    this->_nickname = name;
}

void Client::setUsername(std::string username){
    this->_username = username;
}

void Client::setRealname(std::string realname){
    this->_realname = realname;
}