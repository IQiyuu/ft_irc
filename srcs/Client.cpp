#include "Client.hpp"

Client::Client(void) {
    std::cout << "Client : <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::CLient(std::string name, std::string nickname, std::string username, int socketfd): _name(name), _nickname(nickname), _username(username), _socketFd(socketfd){
    std::cout << "Client :" << _name << GREEN << " created" << RESET << std::endl;
}

Client::~Client(void) {
    std::cout << "Client :" << _name << RED << " deleted" << RESET << std::endl;
}

std::string getName(void){
    return this->_name;
}

std::string getUsername(void){
    return this->_username;
}

std::string getRealname(void){
    return this->_realname;
}

int getSocketFd(void){
    return this->_socketFd;
}

void setName(std::string name){
    this->_name = name;
}

void setUsername(std::string username){
    this->_username = username;
}

void setRealname(std::string realname){
    this->_realname = realname;
}