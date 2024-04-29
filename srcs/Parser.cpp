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

    if (args.find(' ') != std::string::npos)    
        command = args.substr(0, args.find(' '));
    else
        command = args;
    args.erase(0, args.find(' ') + 1);

    if (command == "NAMES")
        this->_commands["BAN"]->execute(sender, args);

    std::map<std::string, Command *>::iterator it;
    for(it = this->_commands.begin(); it != this->_commands.end(); ++it) {
        if (!command.compare(it->first)) {
            std::string params;
            if (args.find('\n') != std::string::npos) {
                params = args.substr(0, args.find('\r'));
                args.erase(0, args.find('\n') + 1);
            }
            else {
                params = args;
                args = "";
            }
            it->second->execute(sender, params);
            if (!args.empty())
                parse(sender, args);
            if (!command.compare("QUIT"))
                return 1;
            return 0;
        }
    }
    std::cout << "Server: " << RED << "`" << command << "` Command not found." << RESET << std::endl;
    if (args.find('\n') != std::string::npos) {
        args.erase(0, args.find('\n') + 1);
        parse(sender, args);
    }
    return 0;
}