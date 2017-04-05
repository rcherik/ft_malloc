/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 20:38:04 by rcherik           #+#    #+#             */
/*   Updated: 2015/03/19 13:59:01 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_all_block	*g_all = NULL;

static void		*ft_add_block(t_block **block, size_t size)
{
	t_block		*ret;
	t_block		*tmp;

	tmp = *block;
	ret = (void *)tmp->data + size;
	ret->next = tmp->next;
	ret->prev = tmp;
	ret->size = tmp->size - size - BLOCK;
	ret->type = tmp->type;
	ret->free = 1;
	ret->ptr = (char *)ret + BLOCK;
	if (tmp->next)
		tmp->next->prev = ret;
	tmp->next = ret;
	tmp->size = size;
	tmp->free = 0;
	return (&(tmp->data));
}

static t_block	*ft_mmap(long map_len, unsigned int type)
{
	t_block		*block;

	if ((block = mmap(NULL, map_len, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == (void *)-1)
		return (NULL);
	block->prev = NULL;
	block->next = NULL;
	block->size = map_len - BLOCK;
	block->type = type;
	block->free = 1;
	block->ptr = (char *)block + BLOCK;
	g_all->ref = (char *)block + map_len;
	return (block);
}

static void		*smalloc(size_t size, long ms, unsigned int type, t_block **ls)
{
	t_block		*tmp;
	t_block		*tmp2;

	if (!(*ls))
	{
		if ((*ls = ft_mmap(ms, type)) == NULL)
			return (NULL);
	}
	tmp = *ls;
	while (tmp && !(tmp->free && tmp->size > (size + BLOCK)))
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp->ptr == ((char *)tmp + BLOCK))
		return (ft_add_block(&tmp, size));
	else
	{
		if ((tmp2->next = ft_mmap(ms, type)) == NULL)
			return (NULL);
		tmp2->next->prev = tmp2;
		return (ft_add_block(&(tmp2->next), size));
	}
}

static void		*ft_malloc_large(size_t size, t_block **ls)
{
	t_block		*tmp;

	tmp = *ls;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		if ((tmp->next = ft_mmap(size, 3)) == NULL)
			return (NULL);
		tmp->next->free = 0;
		tmp->next->prev = tmp;
		return (tmp->next->data);
	}
	else
	{
		if ((*ls = ft_mmap(size, 3)) == NULL)
			return (NULL);
		(*ls)->free = 0;
		return ((*ls)->data);
	}
}

void			*malloc(size_t size)
{
	if (size < 1)
		return (NULL);
	if (!g_all)
	{
		if ((g_all = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE,
						MAP_ANON | MAP_PRIVATE, -1, 0)) == NULL)
			return (NULL);
		g_all->tiny = NULL;
		g_all->small = NULL;
		g_all->large = NULL;
		g_all->ref = (char *)g_all + getpagesize();
	}
	if (ALIGN(size) <= N)
		return (smalloc(ALIGN(size), TINY, 1, &(g_all->tiny)));
	else if (ALIGN(size) <= M)
		return (smalloc(ALIGN(size), SMALL, 2, &(g_all->small)));
	else
		return (ft_malloc_large(BIG_ALIGN(size), &(g_all->large)));
	return (NULL);
}
