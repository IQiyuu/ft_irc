#include "Parser.hpp"

Parser::Parser( Server *serv ) {
    _commands["BAN"] = new Ban(serv);
    _commands["CAP"] = new Cap(serv);
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
    _commands["USER"] = new User(serv);
    _commands["WHO"] = new Who(serv);
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
    sender->appendRequest(args);
    if (args.find("\n") == std::string::npos) {
        std::cout << sender->getNickName() << ": " << YELLOW << "All Packages are not received yet." << RESET << std::endl;
        return 0;
    }
    std::string str = sender->getRequest();
    if (str.find(' ') != std::string::npos)    
        command = str.substr(0, str.find(' '));
    else
        command = str;
    str.erase(0, str.find(' ') + 1);

    if (command == "NAMES")
        this->_commands["BAN"]->execute(sender, str);

    std::map<std::string, Command *>::iterator it;
    for(it = this->_commands.begin(); it != this->_commands.end(); ++it) {
        if (!command.compare(it->first)) {
            std::string params;
            if (str.find('\n') != std::string::npos) {
                params = str.substr(0, str.find('\n'));
                str.erase(0, str.find('\n') + 1);
            }
            else {
                params = str;
                str = "";
            }
            it->second->execute(sender, params);
            if (!str.empty())
                parse(sender, str);
            sender->setRequest("");
            if (!command.compare("QUIT"))
                return 1;
            return 0;
        }
    }
    std::cout << "Server: " << RED << "`" << command << "` Command not found." << RESET << std::endl;
    if (str.find('\n') != std::string::npos) {
        str.erase(0, str.find('\n') + 1);
        parse(sender, str);
    }
    return 0;
}