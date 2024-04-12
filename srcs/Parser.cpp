#include "Parser.hpp"

int Parser::parse( std::string input, Server &serv, Client &sender) {
    if (input.find(' ') > input.size()) {
        if (sender.getLock())
            serv.sendTo(serv.getIpFromIndex(0), sender.getIp(), "Enter: `PASS password` to connect");
        return 1;
    }

    std::string command = input.substr(0, input.find(' '));
    std::string arguments = input.substr(input.find(' ') + 1, input.size() - input.find(' ') - 3);
    //std::cout << input.size() - input.find(' ') << " " << input.find(' ') << " " << input.size() << std::endl;
    if (sender.getLock()) {
        if (command == "PASS" && arguments == serv.getPasswrd()) {
            sender.unlock();
            serv.sendTo(serv.getIpFromIndex(0), sender.getIp(), "You are now connected, `NICK nickname` to change you nickname");
        }
        else {
            //std::cout << "*" << input.substr(input.find(' ') + 1, input.size() - input.find(' ') - 3) << "*" << std::endl;
            serv.sendTo(serv.getIpFromIndex(0), sender.getIp(), "Enter `PASS password` to connect");
        }
    }
    else {
        if (command == "NICK") {
            if (arguments.size() < 3)
                return 1;
            sender.setUsername(arguments.substr(0, (arguments.find(' ') > arguments.size() ? arguments.size() : arguments.find(' '))));
            std::string msg = "your nickname has been changed to: " + sender.getUsername();
            serv.sendTo(serv.getIpFromIndex(0), sender.getIp(), msg);
        }
        else if (command == "PRIVMSG") {
            if (input.find(' ') > input.size())
                return 1;
            Client receiver;
            try {
                receiver = serv.getClientByUsername(arguments.substr(0, input.find(' ')));
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return 1;
            }
            std::string data = arguments.substr(input.find(' ') + 1, input.size());
            serv.sendTo(sender.getIp(), receiver.getIp(), data);
        }
        else
            serv.sendAll(sender.getIp(), arguments);
    }
    return 0;
}