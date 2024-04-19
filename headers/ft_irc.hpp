#ifndef FTIRC
#define FTIRC

enum ServStates {
    CREATING,
    LISTENING,
    EXITING
};

class Client;
class Server;
class Channel;

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

#include <vector>
#include <map>

#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Macro.hpp"
#include "Server.hpp"

#endif