/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:59:29 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/17 09:15:37 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_queue
{
	struct s_list	*lst;
	struct s_list	*head;
	struct s_list	*tail;

}					t_queue;


void				*ft_dequeue(struct s_queue *q);
void				ft_enqueue(struct s_queue *q, void *n, size_t size);
t_queue				*ft_queuenw(void *n, size_t size);
t_list				**ft_lstsethead(t_list *elem);
void				ft_two_d_free(void **array);
int					ft_is_whitespace(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlen(const char *str);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *sm, size_t len);
char				**ft_strsplit(char const *s, char c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strdup(const char *str);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_nbrlen(int nbr);
unsigned int		ft_absval(int n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memalloc(size_t size);
char				*ft_strnew(size_t size);
void				ft_memdel(void **ap);
char				*ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
void				ft_putchar(char c);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_putnbr(long long n);
void				ft_putnbr_fd(long long n, int fd);
void				ft_putstr(char *str);
void				ft_putendl(char *str);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				ft_putstr_fd(char const *str, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_strlcat(char *dst, char const *src, size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_lstsort(t_list *begin, int (*cmp)(void *, void *, void **, int), void **aux, int len);
void				ft_lstforeach(t_list *lst, void (*f)(), void **aux, int len);
int					ft_digslct(int k, int n);
int					ft_exp(int base, int power);
#endif
