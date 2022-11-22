/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:16:49 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:16:51 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_vars(double *d, int *n, int *dig, int *dec)
{
	*d = 0.0;
	*n = 0;
	*dig = 0;
	*dec = 0;
}

static void	check_sign(char **s, int *negptr)
{
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*negptr = 1;
		(*s)++;
	}
}

double	ft_strtod(char *s)
{
	double	nbr;
	int		negative;
	int		digits;
	int		decimals;

	while (*s == ' ')
		s++;
	init_vars(&nbr, &negative, &digits, &decimals);
	check_sign(&s, &negative);
	while (ft_isdigit(*s) || (digits++))
		nbr = nbr * 10.0 + (*(s++) - '0');
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s) && (++digits) && (++decimals))
		{
			nbr = nbr * 10.0 + (*s - '0');
			s++;
		}
	}
	while (decimals--)
		nbr /= 10.0;
	if (negative)
		return (-nbr);
	return (nbr);
}
