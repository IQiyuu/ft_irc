#ifndef MACROIRC
#define MACROIRC

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

#define ERROR -1
#define SUCCESS 0
#define POLL_TIMEOUT 100
#define BUF_SIZE 1024
#define MAX_CON 100

#define WELCOME_RPL(nn) "001 " + nn + " :Welcome to the ft_irc, " + nn + "!\r\n"

#define NO_TOPIC(nn, chan) "331 " + nn + " " + chan + " :no Topic is set\r\n"

#define CLIENTLIST(clist, nn, chan) "353 " + nn + " = " + chan + " :" + clist + "\r\n"
#define ENDOF_CLIENTLIST(nn, chan) "366 " + nn + " " + chan  + " :End of /NAMES list.\r\n"

#define JOIN_RPL(nn, chan) ":" + nn + " JOIN " + chan + "\r\n"
#define PRIVMSG_RPL(nn, cible, msg) ":" + nn + " PRIVMSG " + cible + " :" + msg + "\r\n"

#endif