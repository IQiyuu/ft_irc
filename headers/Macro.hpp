#ifndef MACROIRC
#define MACROIRC

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define LIGHT_PINK "\033[38;2;255;112;166m"
#define DARK_PINK "\033[38;2;79;19;42m"
#define PINK "\033[38;2;255;59;133m"
#define RESET "\033[0m"

#define ERROR -1
#define SUCCESS 0
#define POLL_TIMEOUT 100
#define BUF_SIZE 1024
#define MAX_CON 100

#define WELCOME_RPL(nn, cli) "001 " + nn + " :Welcome to the Internet Relay Network!"

#define NO_TOPIC(nn, chan) "331 " + nn + " " + chan + " : no Topic is set."

#define WHOCHAN(nn, chan, nn2, hn, uname) "352 " + nn + " " + chan + " ~" + uname + " ft_irc " + hn + " H :0 0PNH " + nn2
#define ENDOF_WHOCHAN(nn, chan) "315 " + nn + " " + chan  + " : End of WHO list"


#define CLIENTLIST(clist, nn, chan) "353 " + nn + " = " + chan + " :" + clist
#define ENDOF_CLIENTLIST(nn, chan) "366 " + nn + " " + chan + " : End of /NAMES list"

#define JOIN_RPL(cli, chan) ":" + cli + " JOIN :" + chan
#define PRIVMSG_RPL(nn, cible, msg) ":" + nn + " PRIVMSG " + cible + " " + msg
#define CAPLS_RPL() "CAP * LS : none"
#define CAPEND_RPL() "CAP * ACK : End of CAP negotiation"
#define PART_RPL(cli, chan, rea) ":" + cli + " PART " + chan + " " + rea + "."
#define QUIT_RPL(nn, rea) ":" + nn + " QUIT " + rea
#define NICK_RPL(ann, nn) ":" + ann + " NICK " + nn
#define PING_RPL(cli, arg) ":" + cli + " PONG " + arg
#define INVITE_RPL(cli, tar, chan) ":" + cli + " INVITE " + tar + " " + chan
#define INVITING_RPL(cli, nn, tar, chan) "341 " + nn + " " + tar + " " + chan
#define MODE_RPL(nn, mode) "MODE " + nn + " :" + mode
#define TOPIC_RPL(cli, chan, topic) "332 " + cli + " " + chan + " :" + topic

/* USER */
#define ALREADYREGISTERED_ERR(cli) "462 " + cli + " :You may not reregister."

/* PASS */
#define PASSMISMATCH_ERR(cli) "464 " + cli + " :Password incorrect."

/* OVERALL */
#define NEEDMOREPARAMS_ERR(cli, comm) "461 " + cli + " " + comm + " :Not enough parameters"
#define UNKNOWNCOMMAND_ERR(cli, comm) "421 " + cli + " " + comm + " :Unknow command"
#define NOSUCHCHANNEL_ERR(cli, chan) "403 " + cli + " " + chan + " :No such channel"
#define NOTONCHANNEL_ERR(cli, chan) "442 " + cli + " " + chan + " :You're not on that channel"
#define CHANOPRIVNEEDED_ERR(cli, chan) "482 " + cli + " " + chan + " :You're not channel operator"
#define USERONCHANNEL_ERR(cli, target, chan) "443 " + cli + " " + target + " " + " " + chan + ":is already on channel."
#define NOSUCHNICK_ERR(cli, tar) "401 " + cli + " " + tar + " : No such nick/channel"

/* JOIN */
#define INVITEONLYCHAN_ERR(cli, chan) "473 " + cli + " " + chan + " :Cannot join channel (+i)"
#define BADKEYCHANNEL_ERR(cli, chan) "475 " + cli + " " + chan + " :Cannot join channel (+k)"
#define CHANFULL_ERR(cli, chan)  "471 " + cli + " " + chan + " :Cannot join channel (+l)"

/* PRIVMSG */
#define NOTEXTTOSEND_ERR(cli) "412 " + cli + " :No text to send"

/* NICK */
#define NICKNAMEINUSE_ERR(cli, nn) "433 " + cli + " " + nn + " :Nickname is already in use"
#define NICKNAMERRONEUS_ERR(cli, nn) "432 " + cli + " " + nn + " :Erroneus nickname"

/* TOPIC */
#define CLEARING_TOPIC(chan) "Clearing the topic on " + chan


/* INVITE */
#define INVITEONLY_ERR(cli, chan) "473 " + cli + " " + chan + " :Cannot join channel (+i)"

#endif

// #ifndef NUMERICAL_REPLIES_HPP
// #define NUMERICAL_REPLIES_HPP

// void	sendServerRpl(int const client_fd, std::string client_buffer);

// # define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

// # define RPL_WELCOME(user_id, nickname) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
// # define RPL_YOURHOST(client, servername, version) (":localhost 002 " + client + " :Your host is " + servername + " (localhost), running version " + version + "\r\n")
// # define RPL_CREATED(client, datetime) (":localhost 003 " + client + " :This server was created " + datetime + "\r\n")
// # define RPL_MYINFO(client, servername, version, user_modes, chan_modes, chan_param_modes) (":localhost 004 " + client + " " + servername + " " + version + " " + user_modes + " " + chan_modes + " " + chan_param_modes + "\r\n")
// # define RPL_ISUPPORT(client, tokens) (":localhost 005 " + client + " " + tokens " :are supported by this server\r\n")

// # define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n")

// // INVITE
// # define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters.\r\n")
// # define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " #" + channel + " :No such channel\r\n")
// # define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " #" + channel + " :The user is not on this channel.\r\n")
// # define ERR_USERONCHANNEL(client, nick, channel) (":localhost 443 " + client + " " + nick + " #" + channel + " :Is already on channel\r\n")
// # define RPL_INVITING(user_id, client, nick, channel) (user_id + " 341 " + client + " " + nick + " #" + channel + "\r\n")
// # define RPL_INVITE(user_id, invited, channel) (user_id + " INVITE " + invited + " #" + channel + "\r\n")

// // JOIN
// # define RPL_JOIN(user_id, channel) (user_id + " JOIN :#" +  channel + "\r\n")
// # define ERR_BANNEDFROMCHAN(client, channel) ("474 " + client + " #" + channel + " :Cannot join channel (+b)\r\n")
// # define ERR_BADCHANNELKEY(client, channel) ("475 " + client + " #" + channel + " :Cannot join channel (+k)\r\n")

// // KICK
// # define ERR_USERNOTINCHANNEL(client, nickname, channel) ("441 " + client + " " + nickname + " #" + channel + " :They aren't on that channel\r\n")
// // # define ERR_CHANOPRIVSNEEDED(client, channel) ("482 " + client + " #" +  channel + " :You're not channel operator\r\n")
// # define RPL_KICK(user_id, channel, kicked, reason) (user_id + " KICK #" + channel + " " + kicked + " " + reason + "\r\n")

// // KILL
// # define ERR_NOPRIVILEGES(client) ("481 " + client + " :Permission Denied- You're not an IRC operator\r\n")
// # define RPL_KILL(user_id, killed, comment) (user_id + " KILL " + killed + " " + comment + "\r\n")

// // MODE
// /* user mode */
// #define MODE_USERMSG(client, mode) (":" + client + " MODE " + client + " :" + mode + "\r\n")
// #define ERR_UMODEUNKNOWNFLAG(client) (":localhost 501 " + client + " :Unknown MODE flag\r\n")
// #define ERR_USERSDONTMATCH(client) ("502 " + client + " :Cant change mode for other users\r\n")
// #define RPL_UMODEIS(client, mode) (":localhost 221 " + client + " " + mode + "\r\n")
// /* channel mode */
// #define MODE_CHANNELMSG(channel, mode) (":localhost MODE #" + channel + " " + mode + "\r\n")
// #define MODE_CHANNELMSGWITHPARAM(channel, mode, param) (":localhost MODE #" + channel + " " + mode + " " + param + "\r\n")
// #define RPL_CHANNELMODEIS(client, channel, mode) (":localhost 324 " + client + " #" + channel + " " + mode + "\r\n")
// #define RPL_CHANNELMODEISWITHKEY(client, channel, mode, password) (":localhost 324 " + client + " #" + channel + " " + mode + " " + password + "\r\n")
// #define ERR_CANNOTSENDTOCHAN(client, channel) ("404 " + client + " #" + channel + " :Cannot send to channel\r\n")
// #define ERR_CHANNELISFULL(client, channel) ("471 " + client + " #" + channel + " :Cannot join channel (+l)\r\n")
// #define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " #" + channel + " :You're not channel operator\r\n")
// #define ERR_INVALIDMODEPARAM(client, channel, mode, password) ("696 " + client + " #" + channel + " " + mode + " " + password + " : password must only contained alphabetic character\r\n")
// // RPL_ERR a broadcoast quand user pas +v ou operator veut parler
//       // dans notre cas c'était tiff (client) qui voulait send a message
//       // :lair.nl.eu.dal.net 404 tiff #pop :Cannot send to channel
// #define RPL_ADDVOICE(nickname, username, channel, mode, param) (":" + nickname + "!" + username + "@localhost MODE #" + channel + " " + mode + " " + param + "\r\n")

// // MOTD
// #define ERR_NOSUCHSERVER(client, servername) (":localhost 402 " + client + " " + servername + " :No such server\r\n")
// #define ERR_NOMOTD(client) (":localhost 422 " + client + " :MOTD File is missing\r\n")
// #define RPL_MOTDSTART(client, servername) (":localhost 375 " + client + " :- " + servername + " Message of the day - \r\n")
// #define RPL_MOTD(client, motd_line) (":localhost 372 " + client + " :" + motd_line + "\r\n")
// #define RPL_ENDOFMOTD(client) (":localhost 376 " + client + " :End of /MOTD command.\r\n")


// // NAMES
// # define RPL_NAMREPLY(client, symbol, channel, list_of_nicks) (":localhost 353 " + client + " " + symbol + " #" + channel + " :" + list_of_nicks + "\r\n")
// # define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " #" + channel + " :End of /NAMES list.\r\n")

// // NICK
// # define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :There is no nickname.\r\n")
// # define ERR_ERRONEUSNICKNAME(client, nickname) (":localhost 432 " + client + " " + nickname + " :Erroneus nickname\r\n")
// # define ERR_NICKNAMEINUSE(client, nickname) (":localhost 433 " + client + " " + nickname + " :Nickname is already in use.\r\n")
// # define RPL_NICK(oclient, uclient, client) (":" + oclient + "!" + uclient + "@localhost NICK " +  client + "\r\n")

// // NOTICE
// # define RPL_NOTICE(nick, username, target, message) (":" + nick + "!" + username + "@localhost NOTICE " + target + " " + message + "\r\n")

// // OPER
// # define ERR_NOOPERHOST(client) ("491 " + client + " :No O-lines for your host\r\n")
// # define RPL_YOUREOPER(client) ("381 " + client + " :You are now an IRC operator\r\n")

// // PART
// # define RPL_PART(user_id, channel, reason) (user_id + " PART #" + channel + " " + (reason.empty() ? "." : reason ) + "\r\n")

// // PASS
// # define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect.\r\n")

// // PING
// # define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")

// // QUIT
// # define RPL_QUIT(user_id, reason) (user_id + " QUIT :Quit: " + reason + "\r\n")
// # define RPL_ERROR(user_id, reason) (user_id + " ERROR :" + reason + "\r\n")

// // PRIVMSG
// # define ERR_NOSUCHNICK(client, target) ("401 " + client + " " + target + " :No such nick/channel\r\n")
// # define ERR_NORECIPIENT(client) ("411 " + client + " :No recipient given PRIVMSG\r\n")
// # define ERR_NOTEXTTOSEND(client) ("412 " + client + " :No text to send\r\n")
// # define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n")

// // TOPIC
// # define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " #" + channel + " " + topic + "\r\n")
// # define RPL_NOTOPIC(client, channel) (":localhost 331 " + client + " #" + channel + " :No topic is set\r\n")

// // USER
// # define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister.\r\n")







// #endif