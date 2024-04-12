#include "Client.hpp"

Client::Client( std::string username, int ip, int client_socket ): _username(username), _ip(ip), _connectionTime(time(0)), _locked(true) {
    _pfd.fd = client_socket;
    _pfd.events = POLLIN | POLLPRI;
    std::cout << "Client \033[32mcreated\033[0m" << std::endl;
}

Client::~Client( void ) {
    close(this->_pfd.fd);
    std::cout << "Client \033[31mDestructed\033[0m" << std::endl;
}

Client &Client::operator=( const Client &ref ) {
    this->_username = ref._username;
    this->_ip = ref._ip;
    this->_pfd = ref._pfd;
    this->_connectionTime = ref._connectionTime;
    this->_locked = true;
    return *this;
}

Client::Client( const Client &ref ) {
    *this = ref;
}

std::string Client::whoAmI( void ) const {
    std::string res = "Connected since: ";
    res += ctime(&(this->_connectionTime));
    res += "\nUsername: ";
    res += this->_username;
    res += "\nIP: ";
    res += this->_ip;
    res += "\nChannels: General\n";
    return res;
}

std::string Client::getUsername( void ) const {
    return this->_username;
}

int Client::getIp( void ) const {
    return this->_ip;
}

bool    Client::getLock( void ) const {
    return this->_locked;
}

struct pollfd Client::getPollFd( void ) const {
    return this->_pfd;
}

void    Client::setUsername( std::string nName ) {
    this->_username = nName;
}

void Client::unlock( void ) {
    if (this->_locked)
        this->_locked = false;
}