/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 20:35:06 by rcherik           #+#    #+#             */
/*   Updated: 2014/04/20 20:56:15 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_puthex(int n)
{
	char	c;

	if (n >= 10)
		c = n + 55;
	else
		c = n + 48;
	write(1, &c, 1);
}

static void	ft_putaddr(long n)
{
	if (n < 16)
		ft_puthex(n);
	else
	{
		ft_putaddr(n / 16);
		ft_puthex(n % 16);
	}
}

void		ft_printaddr(void *addr)
{
	write(1, "0x", 2);
	ft_putaddr((long)addr);
}
