/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 21:28:54 by rcherik           #+#    #+#             */
/*   Updated: 2014/04/20 21:29:01 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t		index;
	char		*str;

	index = 0;
	str = s;
	while (index < n)
	{
		*str = 0;
		str++;
		index++;
	}
	s = str;
}
