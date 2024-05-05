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

#define WELCOME_RPL(nn) "001 " + nn + " :Welcome to the ft_irc, " + nn + "!"

#define NO_TOPIC(nn, chan) "331 " + nn + " " + chan + " :no Topic is set."

#define WHOCHAN(nn, chan, nn2, hn, uname) "352 " + nn + " " + chan + " ~" + uname + " ft_irc " + hn + " H :0 0PNH " + nn2
#define ENDOF_WHOCHAN(nn, chan) "315 " + nn + " " + chan  + " :End of WHO list"


#define CLIENTLIST(clist, nn, chan) "353 " + nn + " = " + chan + " :" + clist
#define ENDOF_CLIENTLIST(nn, chan) "366 " + nn + " " + chan + " :End of /NAMES list"

#define JOIN_RPL(nn, chan) ":" + nn + " JOIN :" + chan
#define PRIVMSG_RPL(nn, cible, msg) ":" + nn + " PRIVMSG " + cible + " " + msg
#define CAPLS_RPL() "CAP * LS :multi_prefix"
#define CAPEND_RPL() "CAP * ACK :End of CAP negotiation"
#define PART_RPL(nn, chan, rea) ":" + nn + " PART " + chan + " :" + rea
#define QUIT_RPL(nn, rea) ":" + nn + " QUIT " + rea
#define NICK_RPL(ann, nn) ":" + ann + " NICK :" + nn
#define PING_RPL(nn, arg) "PONG " + arg
#define INVITE_RPL(sender, target, chan) ":" + sender + " INVITE " + target + " :" + chan

#endif