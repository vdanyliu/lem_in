/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parcer_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:55:11 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/16 17:51:12 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				lm_create_link(t_room *room1, t_room *room2)
{
	t_lroom	*buff;

	buff = room1->link;
	if (room1->link == NULL)
	{
		room1->link = (t_lroom*)malloc(sizeof(t_lroom));
		room1->link->room = room2;
		room1->link->next = NULL;
		return ;
	}
	while (buff->next && buff->room != room2)
		buff = buff->next;
	if (buff->room == room2)
		lm_error(7);
	buff->next = (t_lroom*)malloc(sizeof(t_lroom));
	buff->next->room = room2;
	buff->next->next = NULL;
}

static t_room		*lm_find_room(t_lem *lem, char *name)
{
	t_room	*curr;

	curr = lem->rooms;
	while (curr && ft_strcmp(curr->name, name) != 0)
		curr = curr->next;
	if (curr == NULL)
		lm_error(67);
	return (curr);
}

static void			lm_add_link(t_lem *lem, char *r1, char *r2)
{
	t_room	*room1;
	t_room	*room2;

	room1 = lm_find_room(lem, r1);
	room2 = lm_find_room(lem, r2);
	lm_create_link(room1, room2);
	lm_create_link(room2, room1);
}

void				lm_parce_link(char *gnl, t_lem *lem)
{
	char	**split;

	split = ft_strsplit(gnl, '-');
	if (split[0] == 0 || split[1] == 0 || split[2] != 0)
		lm_error(66);
	lm_add_link(lem, split[0], split[1]);
	lm_free_split(split);
}
