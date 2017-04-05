/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 20:34:20 by rcherik           #+#    #+#             */
/*   Updated: 2015/03/19 15:17:17 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_all_block	*g_all;

static void		ft_check_munmap(t_block *block)
{
	t_block	*tmp;

	tmp = g_all->large;
	while (g_all->large)
	{
		if (g_all->large == block)
		{
			if (tmp == g_all->large)
				tmp = g_all->large->next;
			if (g_all->large->prev)
				g_all->large->prev->next = g_all->large->next;
			if (g_all->large->next)
				g_all->large->next->prev = g_all->large->prev;
			g_all->large = tmp;
			break ;
		}
		if (g_all->large)
			g_all->large = g_all->large->next;
	}
	while (g_all->large && g_all->large->prev)
		g_all->large = g_all->large->prev;
	if (munmap(block, block->size + BLOCK) == -1)
		write(1, "free error\n", 11);
}

static t_block	*ft_merge(t_block *block)
{
	if (block->next)
	{
		block->size += block->next->size + BLOCK;
		block->next = block->next->next;
	}
	if (block->next)
		block->next->prev = block;
	return (block);
}

static int		ft_check(void *ptr)
{
	t_all_block		*tmp;

	tmp = g_all;
	if (!tmp)
		return (0);
	while (tmp->tiny)
	{
		if (tmp->tiny->data == ptr)
			return (1);
		tmp->tiny = tmp->tiny->next;
	}
	while (tmp->small)
	{
		if (tmp->small->data == ptr)
			return (1);
		tmp->small = tmp->small->next;
	}
	while (tmp->large)
	{
		if (tmp->large->data == ptr)
			return (1);
		tmp->large = tmp->large->next;
	}
	return (0);
}

static void		check_last(void *ptr, t_block *block)
{
	t_all_block		*tmp;
	t_block			*type;

	tmp = g_all;
	if (!tmp)
		return ;
	if (block->type == 1)
		type = tmp->tiny;
	else
		type = tmp->small;
	if (type)
	{
		while (type->next)
			type = type->next;
		if (type->data == ptr)
		{
			if (munmap(block, block->size + BLOCK) == -1)
				return ;
		}
	}
}

void			free(void *ptr)
{
	t_block		*tmp;
	char		*s;

	if (ptr == NULL || !ft_check(ptr))
		return ;
	s = (char *)ptr - (BLOCK - 8);
	tmp = (t_block *)s;
	if ((char *)tmp->ptr == ((char *)ptr + 8) && tmp->type < 3)
	{
		tmp->free = 1;
		if (tmp->next && tmp->next->free && tmp->type == tmp->next->type)
			tmp = ft_merge(tmp);
		if (tmp->prev && tmp->prev->free && tmp->type == tmp->prev->type)
			tmp->prev = ft_merge(tmp->prev);
		check_last(ptr, tmp);
		if (tmp)
			ft_bzero(ptr, tmp->size);
	}
	if (tmp->type == 3)
		ft_check_munmap(tmp);
}
