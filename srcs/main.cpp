#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sstream>

int main( int ac, char *av[] ) {
    if (ac != 3) {
        std::cout << "Bad parameters! The program should be launched like: `./ircserv <port> <username>`" << std::endl;
        return 0;
    }

    /* transforme av[1] (le port des arguments) en int */
    std::istringstream is(av[1]);
    int port;
    is >> port;

    int connexionFd;
    int socketFd = socket(AF_INET, SOCK_STREAM, 0); /* creer un socket */
    struct sockaddr_in addr_serveur; /* creer la structure des donnees du socket du serveur */
    bzero(&addr_serveur, sizeof(addr_serveur)); /* on set tout a 0 pour etre sur */
    addr_serveur.sin_family = AF_INET; /* pas encore comprit a quoi ca correspondait exactement AF_INET mais c'est utilise tout le temps en reseau */
    addr_serveur.sin_port = htons(port); /* Port du serveur */
    addr_serveur.sin_addr.s_addr = htonl(INADDR_ANY); /* adresse IP de la machine */

    /* lie le socket avec la structure */
    if (bind(socketFd, (struct sockaddr *) &addr_serveur, sizeof(addr_serveur)) < 0) {
        std::cout << "Binding \033[31mfailed\033[0m" << std::endl;
        return 0;
    }
    std::cout << "Server \033[33mlaunched\033[0m on port " << av[1] << std::endl;

    /* creer une longueur max a la file d attente des demandes de connexion */
    if (listen(socketFd, 10) < 0) {
        std::cout << "Listening \033[31mfailed\033[0m" << std::endl;
        return 0;
    }
    std::cout << "Server \033[33mlistening\033[0m on port " << av[1] << std::endl;

    /* fonction bloquante qui attend une connexion (renvoie le fd du nouveau socket) */
    if ((connexionFd = accept(socketFd, NULL, NULL)) < 0) {
        std::cout << "Connexion \033[31mfailed\033[0m" << std::endl;
        return 0;
    }
    std::cout << "Connexion \033[32msuccessful\033[0m on port " << av[1] << std::endl;
    return 0;
}