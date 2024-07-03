#include "Parser.hpp"

Parser::Parser( Server *serv ) {
    _commands["INVITE"] = new Invite(serv);
    _commands["JOIN"] = new Join(serv);
    _commands["KICK"] = new Kick(serv);
    _commands["MODE"] = new Mode(serv);
    _commands["NICK"] = new Nick(serv);
    _commands["PART"] = new Part(serv);
    _commands["PASS"] = new Pass(serv);
    _commands["PING"] = new Ping(serv);
    _commands["QUIT"] = new Quit(serv);
    _commands["PRIVMSG"] = new PrivMsg(serv);
    _commands["TOPIC"] = new Topic(serv);
    _commands["USER"] = new User(serv);
}

Parser::~Parser( void ) {
    std::map<std::string, Command *>::iterator it;
    for (it = this->_commands.begin(); it != this->_commands.end(); ++it) {
        delete it->second;
    }
}

int    Parser::parse( Client *sender, std::string args ) {
    std::string command;

    if (args.empty())
        return 0;
    if (args.find("\n") == std::string::npos) {
        std::cout << sender->getNickName() << ": " << YELLOW << "All Packages are not received yet." << RESET << std::endl;
        return 0;
    }
    std::string str = args;
    if (str.find(' ') != std::string::npos)    
        command = str.substr(0, str.find(' '));
    else
        command = str;
    str.erase(0, str.find(' ') + 1);

    std::map<std::string, Command *>::iterator it;
    for(it = this->_commands.begin(); it != this->_commands.end(); ++it) {
        if (!command.compare(it->first)) {
            std::string params;
            if (str.find('\n') != std::string::npos) {
                params = str.substr(0, str.find('\r'));
                str.erase(0, str.find('\n') + 1);
            }
            else {
                params = str;
                str = "";
            }
            std::cout << "Client Sent: " << DARK_PINK << command << LIGHT_PINK << " " << params << RESET << std::endl;
            it->second->execute(sender, params);
            if (!command.compare("QUIT"))
                return 1;
            if (sender->getState() == BADPASS) {
                sender->setState(NONE);
                return 0;
            }
            if (!str.empty())
                parse(sender, str);
            return 0;
        }
    }
    std::cout << "Server: " << RED << "`" << command << "` Command not found. (" << str << ")" << RESET << std::endl;
    if (str.find('\n') != std::string::npos) {
        str.erase(0, str.find('\n') + 1);
        std::cout << str << std::endl;
        parse(sender, str);
    }
    return 0;
}