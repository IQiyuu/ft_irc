#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define SIZE 1024

int main( int ac, char *av[] ) {
    if (ac != 3) {
        std::cout << "Bad parameters! The program should be launched like: `./ircserv <port> <username>`" << std::endl;
        return 0;
    }

    /* transforme av[1] (le port des arguments) en int */
    std::istringstream is(av[1]);
    int port;
    is >> port;

    //int connexionFd;
    int servSocket = socket(AF_INET, SOCK_STREAM, 0); /* creer un socket */
    struct sockaddr_in addr_serveur; /* creer la structure des donnees du socket du serveur */

    addr_serveur.sin_family = AF_INET; /* pas encore comprit a quoi ca correspondait exactement AF_INET mais c'est utilise tout le temps en reseau */
    addr_serveur.sin_port = htons(port); /* Port du serveur */
    addr_serveur.sin_addr.s_addr = htonl(INADDR_ANY); /* adresse IP de la machine */

    /* lie le socket avec la structure */
    if (bind(servSocket, (struct sockaddr *) &addr_serveur, sizeof(addr_serveur)) < 0) {
        std::cout << "Binding \033[31mfailed\033[0m" << std::endl;
        return 0;
    }
    std::cout << "Server \033[33mlaunched\033[0m on port " << av[1] << std::endl;

    /* creer une longueur max a la file d attente des demandes de connexion */
    if (listen(servSocket, 5) < 0) {
        std::cout << "Listening \033[31mfailed\033[0m" << std::endl;
        return 0;
    }
    std::cout << "Server \033[33mlistening\033[0m on port " << av[1] << std::endl;

    // /* fonction bloquante qui attend une connexion (renvoie le fd du nouveau socket) */
    // if ((connexionFd = accept(servSocket, NULL, NULL)) < 0) {
    //     std::cout << "Connexion \033[31mfailed\033[0m" << std::endl;
    //     return 0;
    // }
    // std::cout << "Connexion \033[32msuccessful\033[0m on port " << av[1] << std::endl;

    // FILE *out;
    // int fd2;
    // fd2 = dup(connexionFd);
    // out = fdopen(fd2, "w");
    // fputs("COUCOU\n", out);

    // int poll(struct pollfd *fds, nfds_t nfds, int délai);

    int useClient = 0;
    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = servSocket;
    pollfds[0].events = POLLIN | POLLPRI;

    for (int i = 1; i < MAX_CLIENTS; i++)
    {
        pollfds[i].fd = 0;
        pollfds[i].events = POLLIN | POLLPRI;
    }

    //close(connexionFd);
    //close(servSocket);
    //addr_serveur.sin_port = 0;
    while (1)
    {
        // printf("useClient => %d\n", useClient);
        int pollResult = poll(pollfds, useClient + 1, 10);
        if (pollResult > 0)
        {
            if (pollfds[0].revents & POLLIN)
            {
                struct sockaddr_in cliaddr;
                socklen_t addrlen = sizeof(cliaddr);
                int client_socket = accept(servSocket, (struct sockaddr *)&cliaddr, &addrlen);
                printf("accept success %s\n", inet_ntoa(cliaddr.sin_addr));
                for (int i = 1; i < MAX_CLIENTS; i++)
                {
                    if (pollfds[i].fd == 0)
                    {
                        pollfds[i].fd = client_socket;
                        pollfds[i].events = POLLIN | POLLPRI;
                        useClient++;
                        break;
                    }
                }
            }
            for (int i = 1; i < MAX_CLIENTS; i++)
            {
                if (pollfds[i].fd > 0 && pollfds[i].revents & POLLIN)
                {
                    char buf[SIZE];
                    int bufSize = read(pollfds[i].fd, buf, SIZE - 1);
                    if (bufSize == -1)
                    {
                        printf("CLOSED\n");
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        useClient--;
                    }
                    else if (bufSize == 0)
                    {
                        printf("CLOSED\n");
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        useClient--;
                    }
                    else
                    {
                        buf[bufSize] = '\0';
                        printf("From client: %s\n", buf);
                        for (int x = 1; x < MAX_CLIENTS; x++) {
                            /* fetsockname, getprotobyname, gethostbyname, getaddrinfo*/
                            if (x != i && pollfds[x].fd != 0) {
                                write(pollfds[x].fd, buf, strlen(buf));
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}