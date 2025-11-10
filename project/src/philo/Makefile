CC = cc -c -Wall -Wextra -Werror -g
NAME = philosophers.a

INC = -I ../../includes
LIB = ../../library

SRCS = \
main.c utils.c print.c routine.c thread_action.c init.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $^ -o $@ $(INC)

$(NAME): $(OBJS)
	@mkdir -p $(LIB)
	@ar -rcs $(LIB)/$(NAME) $^

clean:
	@rm -f $(OBJS) 

fclean: clean
	@rm -f $(LIB)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
