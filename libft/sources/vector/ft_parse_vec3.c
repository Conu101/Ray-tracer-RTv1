/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_vec3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:38:49 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/20 23:10:56 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

t_vec3	ft_parse_vec3(char *str)
{
	t_vec3	v;
	char	*token;

	str = ft_strstr(str, " ");
	token = ft_strtok(str, ' ');
	v.x = ft_strtod(token);
	token = ft_strtok(NULL, ' ');
	v.y = ft_strtod(token);
	token = ft_strtok(NULL, ' ');
	v.z = ft_strtod(token);
	return (v);
}
