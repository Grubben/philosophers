NAME		= philo

## COMPILATION
CC			= cc
# Compilation Flags
CFLAGS		= -g3 -Wall -Wextra -Werror -pthread -fsanitize=thread


# Removal Flags. Not sure if necessary
RM			= rm -rf

SRCS		= $(wildcard src/*.c)

OBJS		= $(SRCS:.c=.o)

$(NAME)		: $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o			: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

all			: $(NAME)


clean		:
			$(RM) $(OBJS)

fclean		: clean
			$(RM) $(NAME)

re			: fclean $(NAME)

.PHONY		: re fclean clean all
