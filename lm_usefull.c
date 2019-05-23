/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_usefull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:47:28 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/25 16:47:33 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 	all_is_num(char *str)
{
	if (*str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}

void	lm_free_split(char **str)
{
	char	**buff;

	buff = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(buff);
}

t_room				*lm_last_room(t_lem *lem)
{
	t_room	*last;

	last = lem->rooms;
	if (!last)
		lm_error(10);
	while (last->next)
		last = last->next;
	return (last);
}