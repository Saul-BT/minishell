/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:15:42 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int base, int exp)
{
	int	result;

	if (exp == 0)
		return (1);
	result = base;
	while (--exp)
		result *= base;
	return (result);
}

int	ft_count_digits(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int		i;
	int		neg;
	int		result_len;
	char	*result;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n = (int) n;
	neg = 0;
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	result_len = ft_count_digits(n);
	result = malloc((result_len + neg + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (neg)
		result[i++] = '-';
	while (result_len--)
		result[i++] = '0' + (n / ft_pow(10, result_len)) % 10;
	result[i] = '\0';
	return (result);
}
