/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 15:03:36 by rcherik           #+#    #+#             */
/*   Updated: 2015/03/19 15:10:45 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*ft_resize(size_t size, void *ptr)
{
	void	*tmp;
	char	*s;
	t_block	*block;

	if ((tmp = malloc(size)) == NULL)
		return (NULL);
	s = (char *)ptr - (BLOCK - 8);
	block = (t_block *)s;
	size = block->size > size ? size : block->size;
	tmp = ft_memcpy(tmp, ptr, size);
	free(ptr);
	return (tmp);
}

void		*calloc(size_t count, size_t size)
{
	return (malloc(count * size));
}

void		*reallocf(void *ptr, size_t size)
{
	return (realloc(ptr, size));
}

void		*valloc(size_t size)
{
	return (malloc(size));
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*tmp;
	char	*s;

	if (ptr == NULL)
		return (malloc(size));
	s = (char *)ptr - (BLOCK - 8);
	tmp = (t_block *)s;
	if (tmp->size == size)
		return (ptr);
	if ((char *)tmp->ptr == ((char *)ptr + 8))
		return (ft_resize(size, ptr));
	if (size == 0)
	{
		free(ptr);
		return (malloc(1));
	}
	return (NULL);
}
