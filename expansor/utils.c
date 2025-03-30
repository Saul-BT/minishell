/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:09:31 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/30 20:10:09 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_valid_var_start_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
