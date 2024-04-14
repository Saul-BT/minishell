NAME = minishell
SRCS = main.c
SRCS += commands/echo.c commands/cd.c commands/pwd.c commands/export.c commands/unset.c commands/env.c commands/exit.c commands/index.c
SRCS += utils/strcmp.c
OBJS=$(SRCS:.c=.o)
READLINE_PATH = vendor/readline

# Compiler stuff
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I $(READLINE_PATH)/include
LNK = -L $(READLINE_PATH)/lib  -lreadline

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) $(LNK) $(OBJS) -o $(NAME)