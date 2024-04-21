#include "Parser.hpp"

Parser::Parser( Server *serv ) {
    _commands["BAN"] = new Ban(serv);
    _commands["INVITE"] = new Invite(serv);
    _commands["JOIN"] = new Join(serv);
    _commands["KICK"] = new Kick(serv);
    _commands["MODE"] = new Mode(serv);
    _commands["NICK"] = new Nick(serv);
    _commands["PASS"] = new Pass(serv);
    _commands["PING"] = new Ping(serv);
    _commands["PONG"] = new Pong(serv);
    _commands["PRIVMSG"] = new PrivMsg(serv);
    _commands["USER"] = new User(serv);
}

Parser::~Parser( void ) {
    std::map<std::string, Command *>::iterator it;
    for (it = this->_commands.begin(); it != this->_commands.end(); ++it) {
        delete it->second;
    }
}

void    Parser::parse( Client *sender, std::string args ) {
    if (args.find(' ') == std::string::npos) {
        if (!args.compare("PING"))
            this->_commands["Ping"]->execute(sender, args);
        if (!args.compare("PONG"))
            this->_commands["Pong"]->execute(sender, args);
        return ;
    }
    
    std::string command = args.substr(0, args.find(' '));
    args.erase(0, args.find(' '));

    std::map<std::string, Command *>::iterator it;
    for(it = this->_commands.begin(); it != this->_commands.end(); ++it) {
        if (!command.compare(it->first)) {
            it->second->execute(sender, args);
            return ;
        }
    }
    std::cout << "Server: " << RED << "Command not found." << RESET << std::endl;
}