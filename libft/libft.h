/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:16:07 by dchantse          #+#    #+#             */
/*   Updated: 2018/11/13 17:33:29 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# define BUFF_SIZE 1
# define IFRET(x, y) if (x) return (y);
# define IF(x, y) if (x) {(y);}

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					get_next_line(const int fd, char **line);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strncpy(char *s2, const char *s1, size_t num);
int					ft_strncmp(const char *s1, const char *s2, size_t num);
char				*ft_strncat(char *s2, const char *s1, size_t num);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *s2, const char *s1);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *str);
char				*ft_strcat(char *s2, const char *s1);
void				*ft_memset(void *kek, int val, size_t num);
int					ft_isdigit(int ch);
int					ft_isalpha(int ch);
int					ft_isalnum(int ch);
void				ft_bzero(void *s, size_t n);
int					ft_atoi(const char *str);
void				*ft_memcpy(void *dest, const void *src, size_t num);
void				*ft_memccpy(void *dest, const void *src, int ch,
		size_t num);
char				*ft_strnstr(const char *str1, const char *str2, size_t num);
void				*ft_memmove(void *dest, const void *src, size_t num);
void				*ft_memchr(const void *mem, int ch, size_t num);
int					ft_memcmp(const void *s1, const void *s2, size_t num);
char				*ft_strchr(const char *str, int sym);
char				*ft_strrchr(const char *str, int sym);
size_t				ft_strlcat(char *dest, const char *src, size_t num);
int					ft_isprint(int c);
int					ft_isascii(int c);
void				*ft_memalloc(size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				*ft_itoa(int n);
char				**ft_strsplit(char const *s, char c);
void				ft_strdel(char **as);
void				ft_putendl_fd(char const *s, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_swap(int *a, int *b);
int					ft_sqrt(int nb);
int					ft_islower(char c);
int					ft_isupper(char c);
size_t				ft_w_c(char const *s, char c);
int					int_size(int n);
#endif
