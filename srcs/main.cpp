#include "ft_irc.hpp"

bool sigint = false;

void signalHandler( int sig ) {
    (void)sig;
    sigint = true;
}

int main(int ac, char *av[]) {
    
    srand(time(NULL));
    // struct sigaction sa;

    // sa.sa_handler = signalHandler;

    // sigemptyset(&sa.sa_mask);

    // sa.sa_flags = 0;

    //sigaction(SIGINT, &sa, NULL);
    signal(SIGINT, &signalHandler);
    if (ac != 3) {
        std::cout << "Error: " << RED << "./ircserv <port> <password>" RESET << std::endl;
        return 0;
    }
    int verif = atoi((char *)av[1]);
    if (av[1][0] == '-') {
        std::cout << "Error :" << RED << " port negatif." << RESET << std::endl;
        return SUCCESS;
    }
    if (verif > 2147483647 || verif < 0)
    {
        std::cout << "Error :" << RED << " `" << av[1] << "' not a valid port." << RESET << std::endl;
        return SUCCESS;
    }
    for (int i = 0; av[1][i]; i++)
    {
        if (!isdigit(av[1][i]))
        {
            std::cout << "Error :" << RED << " `" << av[1][i] << "' not valid in port." << RESET << std::endl;
            return SUCCESS;
        }
    }
    Server serv(av[1], av[2]);
    if (serv.launch() == ERROR)
        return 1;
    if (serv.boucle() == ERROR) 
        return 1;
    return SUCCESS;
}