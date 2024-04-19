#include "ft_irc.hpp"

// void signalHandler(int signum) {
//     std::cout << "Signal SIGINT (" << signum << ") reçu. Le programme continue de s'exécuter." << std::endl;
// }
int main(int ac, char *av[]) {
    
    
    // struct sigaction sa;

    // sa.sa_handler = signalHandler;

    // sigemptyset(&sa.sa_mask);

    // sa.sa_flags = 0;

    //sigaction(SIGINT, &sa, NULL);
    if (ac != 3) {
        std::cout << "Error: " << RED << "./ircserv <port> <password>" RESET << std::endl;
        return 0;
    }
    Server *serv = new Server(av[1], av[2]);
    if (serv->launch() == ERROR) {
        delete serv;
        return 1;
    }
    if (serv->boucle() == ERROR) {
        delete serv;
        return 1;
    }
    delete serv;
    return 0;
}