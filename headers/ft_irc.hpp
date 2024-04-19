#ifndef FTIRC
#define FTIRC

enum ServStates {
    CREATING,
    LISTENING,
    EXITING
};

#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Macro.hpp"
#include "Server.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctime>

#include <vector>
#include <map>

#endif