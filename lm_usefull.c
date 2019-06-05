/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_usefull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:47:28 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/25 17:57:58 by vdanyliu         ###   ########.fr       */
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

t_bfs				*lm_new_bfs_list(t_room *parent, t_room *curr)
{
	t_bfs	*new;

	new = (t_bfs*)malloc(sizeof(t_bfs));
	new->parent = parent;
	new->room = curr;
	new->next = NULL;
	new->pre = NULL;
	new->flags = 0;
	return (new);
}

void				lm_bfs_add_node(t_bfs *head, t_room *from, t_room *room, int i)
{
	static t_bfs *curr = NULL;

	if (i == 1)
	{
		curr = NULL;
		return ;
	}
	curr == NULL ? curr = head : 0;
	curr->next = lm_new_bfs_list(from, room);
	curr->next->pre = curr;
	curr = curr->next;
}