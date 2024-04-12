#ifndef PARSER
#define PARSER

#include "Server.hpp"

class Server;

class Parser {
    public:
        Parser(void) {}
        int parse( std::string input, Server &serv, Client &sender );
};


#endif