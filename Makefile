NAME = minishell
SRCS = main.c signals.c main_utils.c
SRCS += commands/echo.c commands/utils.c commands/cd.c commands/pwd.c commands/export.c commands/unset.c commands/env.c commands/exit.c commands/index.c commands/utils2.c
SRCS += utils/strcmp.c utils/parser.c utils/pipe_split.c utils/pipe_split_utils.c utils/util.c pipes/pipes.c pipes/utils.c utils/error.c
SRCS += tokenizer/tokenizer.c tokenizer/utils.c tokenizer/redir_in.c tokenizer/redir_hered.c tokenizer/redir_out.c tokenizer/handle_quotes.c tokenizer/hered_utils.c
SRCS += expansor/expansor.c expansor/utils.c
OBJS=$(SRCS:.c=.o)
READLINE_PATH = vendor/readline
LIBFT = ./libft
LIBFT_NAME = libft.a

# Compiler stuff
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
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