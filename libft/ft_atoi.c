/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2023/04/10 20:33:32 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	issign(char c)
{
	return (c == '-' || c == '+');
}

int	check_overflow(unsigned long long n, int neg)
{
	if (neg == -1 && n > 9223372036854775807)
		return (0);
	if (neg == 1 && n > 9223372036854775807)
		return (-1);
	return (n);
}

const char	*ignore_blanks(const char *nptr)
{
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	return (nptr);
}

int	ft_atoi(const char *nptr)
{
	int					neg;
	unsigned long long	mod;

	neg = 1;
	mod = 0;
	nptr = ignore_blanks(nptr);
	while (issign(*nptr))
	{
		if (*nptr == '-')
			neg *= -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		mod = (*nptr - '0') + (mod * 10);
		nptr++;
	}
	mod = check_overflow(mod, neg);
	return (mod * neg);
}
