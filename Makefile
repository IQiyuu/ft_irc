NAME = ircserv

F =	main\
	Client\
	Server\
	Channel\
	Parser\
	commands/Command\
	commands/Ban\
	commands/Cap\
	commands/Invite\
	commands/Join\
	commands/Kick\
	commands/Mode\
	commands/Nick\
	commands/Part\
	commands/Pass\
	commands/Ping\
	commands/PrivMsg\
	commands/User\
	commands/Quit\
	commands/Who

S = $(foreach f, $(F), srcs/$(f).cpp)
OBJ = $(S:.cpp=.o)

CFLAGS = -Wall -Werror -Wextra -std=c++98 -Iheaders -fsanitize=address -g

all: $(NAME)
r: re
	./$(NAME)

$(NAME): $(OBJ)
	c++ $(OBJ) $(CFLAGS) -o $(NAME)

.cpp.o:
	c++ -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all