# Lib stuff
NAME = libft.a

H_LIBFT = libft.h

AR = ar rcs

C_FILES_MANDATORY = ft_atoi.c       ft_isalpha.c    ft_itoa.c       ft_memmove.c    ft_split.c      ft_strjoin.c    ft_strmapi.c    ft_strtrim.c \
					ft_bzero.c      ft_isascii.c    ft_memchr.c     ft_memset.c     ft_strchr.c     ft_strlcat.c    ft_strncmp.c    ft_substr.c \
					ft_calloc.c     ft_isdigit.c    ft_memcmp.c     ft_putchar_fd.c ft_strdup.c     ft_strlcpy.c    ft_strnstr.c    ft_tolower.c \
					ft_isalnum.c    ft_isprint.c    ft_memcpy.c     ft_putstr_fd.c  ft_striteri.c   ft_strlen.c     ft_strrchr.c    ft_toupper.c \
					ft_putendl_fd.c ft_putnbr_fd.c  ft_index_of.c

C_FILES_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

O_FILES_MANDATORY=$(C_FILES_MANDATORY:.c=.o)

O_FILES_BONUS=$(C_FILES_BONUS:.c=.o)

# Compiler stuff
CC = gcc

CFLAGS = -Wall -Wextra -Werror


RM = rm -f

all: $(NAME)

$(NAME): $(O_FILES_MANDATORY) $(H_LIBFT)
	$(AR) $(NAME) $(O_FILES_MANDATORY)

bonus: $(O_FILES_BONUS)
	@$(AR) $(NAME) $(O_FILES_BONUS)

clean:
	$(RM) $(O_FILES_MANDATORY) $(O_FILES_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
