/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 20:40:27 by rcherik           #+#    #+#             */
/*   Updated: 2015/03/19 11:38:16 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/resource.h>

# define N 256
# define M 1024
# define TINY getpagesize() * 13
# define SMALL getpagesize() * 25
# define BLOCK sizeof(t_block)
# define ALIGN(x) ((((x - 1) >> 3) << 3) + 8)
# define BIG_ALIGN(x) ((((x - 1) >> 12) << 12) + getpagesize())

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
	int				type;
	int				free;
	void			*ptr;
	char			data[1];
}					t_block;

typedef struct		s_all_block
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
	void			*ref;
}					t_all_block;

void				free(void *ptr);
void				show_alloc_mem(void);
void				ft_printaddr(void *addr);
void				*realloc(void *ptr, size_t size);
void				*malloc(size_t size);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				ft_bzero(void *s, size_t n);
void				ft_putendl(char const *s);
#endif
