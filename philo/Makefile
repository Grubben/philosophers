NAME		= philo

## COMPILATION
CC			= gcc
# Compilation Flags
CFLAGS		= -g3 -Wall -Wextra -Werror


# Removal Flags. Not sure if necessary
RM			= rm -rf

SRCS		= $(wildcard src/*.c)

OBJS		= $(SRCS:.c=.o)

$(NAME)		: $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

%.o		: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

all		: $(NAME)


clean		:
			$(RM) $(OBJS)

fclean		: clean
			$(RM) $(NAME)

re			: fclean $(NAME)

.PHONY		: re fclean clean all
