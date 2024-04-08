#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main( int ac, char *av[] ) {
    if (ac != 3) {
        std::cout << "Bad parameters! The program should be launched like: `./ircserv <port> <username>`" << std::endl;
        return 0;
    }



    int port = 6666;
    int connexionFd;
    int socketFd = socket(AF_INET, SOCK_STREAM, 0); /* creer un socket */
    struct sockaddr_in addr_serveur; /* creer la structure des donnees du socket du serveur */
    bzero(&addr_serveur, sizeof(addr_serveur));
    addr_serveur.sin_family = AF_INET;
    addr_serveur.sin_port = htons(port); /* Port du serveur */
    addr_serveur.sin_addr.s_addr = htonl(INADDR_ANY); /* adresse IP de la machine */
    if (bind(socketFd, (struct sockaddr *) &addr_serveur, sizeof(addr_serveur)) < 0) { /* lie le socket avec la structure */
        std::cout << "Binding failed" << std::endl;
        return 0;
    }
    std::cout << "Server launched on port " << av[1] << std::endl;
    if (listen(socketFd, 10) < 0) { /* creer une longueur max a la file d attente des demandes de connexion */
        std::cout << "Listening failed" << std::endl;
        return 0;
    }
    std::cout << "Server listening on port " << av[1] << std::endl;
    if ((connexionFd = accept(socketFd, NULL, NULL)) < 0) { /* fonction bloquante qui attend une connexion (renvoie le fd du nouveau socket) */
        std::cout << "Connexion failed" << std::endl;
        return 0;
    }
    std::cout << "Connexion successful on port " << av[1] << std::endl;
    return 0;
}