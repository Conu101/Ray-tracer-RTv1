/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:29:50 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/12 00:19:26 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
** Allocate (withmalloc(3)) and returns a “fresh” string ending with  '\0'
** representing the integer n given as argument. Negative numbers must be 
** supported. If the allocation fails,the function returns NULL.
*/

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nbr;
	unsigned int	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		nbr = (unsigned int)(n * -1);
	else
		nbr = (unsigned int)n;
	len = (unsigned int)ft_ndigits(n) + (n < 0);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
