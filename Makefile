NAME = minishell
SRCS = main.c
SRCS += commands/echo.c commands/cd.c commands/pwd.c commands/export.c commands/unset.c commands/env.c commands/exit.c commands/index.c
SRCS += utils/strcmp.c utils/parser.c utils/pipe_split.c utils/util.c
OBJS=$(SRCS:.c=.o)
READLINE_PATH = vendor/readline
LIBFT = ./libft
LIBFT_NAME = libft.a

# Compiler stuff
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I $(LIBFT) #-I $(READLINE_PATH)/include
LNK = -L $(LIBFT) -lft -lreadline #-L $(READLINE_PATH)/lib  -lreadline

all: $(LIBFT_NAME) $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

# Libft include
$(LIBFT_NAME):
	make bonus -C $(LIBFT) $(LIBFT_NAME)

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LNK)