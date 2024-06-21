#ifndef FTIRC
#define FTIRC

enum ServStates {
    CREATING,
    LISTENING,
    EXITING
};

enum ClientStates {
    NONE,
    BADPASS,
    AUTH,
    LOGED
};

class   Client;
class   Server;
class   Channel;
class   Parser;

class   Command;
class   Ban;
class   Invite;
class   Join;
class   Kick;
class   Mode;
class   Nick;
class   Pass;
class   Ping;
class   Pong;
class   PrivMsg;
class   User;

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <strings.h>
#include <netdb.h>

// verif si autorise
#include <algorithm>

#include <vector>
#include <map>

#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Macro.hpp"
#include "Server.hpp"
#include "Parser.hpp"

extern bool sigint;

#endif