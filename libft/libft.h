/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/10 09:30:06 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// Third party libs
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include "unistd.h"

// Declarations
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_node;

// Part 1
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t		ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst,
			const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

// Part 2
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Extended
int		ft_index_of(char *str, char c);

// Bonus
t_node	*ft_lstnew(void *content);
void	ft_lstadd_front(t_node **lst, t_node *new);
int		ft_lstsize(t_node *lst);
t_node	*ft_lstlast(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstdelone(t_node *lst, void (*del)(void *));
void	ft_lstclear(t_node **lst, void (*del)(void *));
void	ft_lstiter(t_node *lst, void (*f)(void *));
t_node	*ft_lstmap(t_node *lst, void *(*f)(void *), void (*del)(void *));

#endif
