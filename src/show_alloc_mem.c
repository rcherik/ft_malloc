/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/19 19:18:17 by rcherik           #+#    #+#             */
/*   Updated: 2015/02/09 16:17:40 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_all_block *g_all;

size_t	malloc_print_tiny(t_block *tiny)
{
	size_t	i;

	i = 0;
	ft_putstr("TINY : ");
	ft_printaddr(tiny);
	ft_putchar('\n');
	while (tiny->next)
	{
		if (tiny->free == 0)
		{
			i += tiny->size;
			ft_printaddr(tiny->data);
			ft_putstr(" - ");
			ft_printaddr((char *)tiny->data + tiny->size);
			ft_putstr(" : ");
			ft_putnbr((int)tiny->size);
			ft_putendl(" octets");
		}
		tiny = tiny->next;
	}
	return (i);
}

size_t	malloc_print_small(t_block *small)
{
	size_t	i;

	i = 0;
	ft_putstr("SMALL : ");
	ft_printaddr(small);
	ft_putchar('\n');
	while (small->next)
	{
		if (small->free == 0)
		{
			i += small->size;
			ft_printaddr(small->data);
			ft_putstr(" - ");
			ft_printaddr((char *)small->data + small->size);
			ft_putstr(" : ");
			ft_putnbr((int)small->size);
			ft_putendl(" octets");
		}
		small = small->next;
	}
	return (i);
}

size_t	malloc_print_large(t_block *large)
{
	size_t	i;

	i = 0;
	ft_putstr("LARGE : ");
	ft_printaddr(large);
	ft_putchar('\n');
	while (large)
	{
		i += large->size;
		ft_printaddr(large->data);
		ft_putstr(" - ");
		ft_printaddr((char *)large->data + large->size);
		ft_putstr(" : ");
		ft_putnbr((int)large->size);
		ft_putendl(" octets");
		large = large->next;
	}
	return (i);
}

void	show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	if (!g_all || !(g_all->tiny || g_all->small || g_all->large))
		return ;
	if (g_all->tiny)
		total = malloc_print_tiny(g_all->tiny);
	if (g_all->small)
		total += malloc_print_small(g_all->small);
	if (g_all->large)
		total += malloc_print_large(g_all->large);
	ft_putstr("Total : ");
	ft_putnbr((int)total);
	ft_putendl(" octets");
}
