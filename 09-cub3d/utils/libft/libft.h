/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemartel <jemartel@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:26:13 by jemartel          #+#    #+#             */
/*   Updated: 2022/02/20 18:34:47 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  LIBFT_H
# define  LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void		*ft_memset(void *ptr, int value, size_t num);
void		*ft_bzero(void *ptr, size_t num);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *src, int value, size_t num);
int			ft_memcmp(const void *first, const void *second, size_t lenght);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *output, const char *src, size_t lenght);
size_t		ft_strlcat(char *output, const char *src, size_t buff);
char		*ft_strchr(const char *str, int compared);
char		*ft_strrchr(const char *str, int compared);
char		*ft_strnstr(const char *str1, const char *str2, size_t len);
int			ft_strncmp(const char *str1, const char *str2, size_t len);
int			ft_atoi(const char *value);
int			ft_isalpha(int str);
int			ft_isdigit(int str);
int			ft_isalnum(int str);
int			ft_isascii(int str);
int			ft_isprint(int str);
int			ft_toupper(int str);
int			ft_tolower(int str);
void		*ft_calloc(size_t lenght, size_t size);
char		*ft_strdup(const char *str);
char		*ft_substr(char const *src, unsigned int start,	size_t end);
char		*ft_strjoin(char *first, char *second);
char		*ft_strtrim(char const *str, char const *set);
char		**ft_split( const char *str, char comp);
char		*ft_itoa(int input);
char		*ft_strmapi(const char *str, char (*fnptr)( unsigned int, char));
void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char str, int fd);
void		ft_putnbr_fd(int input, int fd);
void		ft_putendl_fd(char *str, int fd);
t_list		*ft_lstlast(t_list *currlist);
void		ft_lstadd_back(t_list **currlist, t_list *new);
void		ft_lstadd_front(t_list **currlist, t_list *newnode);
void		ft_lstclear(t_list **currlist, void (*del) (void *));
void		ft_lstdelone(t_list *currlist, void (*del)(void *));
void		ft_lstiter(t_list *currlist, void (*f) (void *));
t_list		*ft_lstlast(t_list *currlist);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstmap(t_list *curr, void *(*f)(void *), void (*del)(void *));
int			ft_lstsize(t_list *currlist);
int			ft_until_this(char *str, char *this);
#endif 
