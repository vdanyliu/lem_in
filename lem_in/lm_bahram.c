/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bahram.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:51:20 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/13 19:58:13 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	lm_bahram_clean_room(t_lem *lem)
{
	t_room	*curr;

	curr = lem->rooms;
	while (curr)
	{
		curr->belong_to = NULL;
		curr = curr->next;
	}
}

static void	lm_bahram_room_link_to_way(t_lem *lem)
{
	t_wroom	*curr;
	t_lroom	*way;

	lm_bahram_clean_room(lem);
	curr = lem->ways;
	while (curr)
	{
		way = curr->list;
		while (way)
		{
			way->room->belong_to = curr;
			way = way->next;
		}
		curr = curr->nextlist;
	}
	lem->start->belong_to = 0;
	lem->finish->belong_to = 0;
}

void		lm_free_t_wroom_copy(t_wroom *ways)
{
	t_wroom	*buff;

	while (ways)
	{
		buff = ways;
		ways = ways->nextlist;
		lm_free_t_wroom(buff);
	}
}

int			lm_bahram(t_lem *lem)
{
	int		pre;
	t_wroom	*way;
	t_wroom	*copy;

	lm_bahram_room_link_to_way(lem);
	while ((way = lm_find_way_bahram(lem)) != 0)
	{
		copy = lm_copy_way(lem->ways);
		pre = lm_calc_turns(lem);
		lm_add_way(lem->ways, way);
		lm_bahram_fix_ways(lem);
		lm_bahram_room_link_to_way(lem);
		if (pre < lm_calc_turns(lem))
		{
			lm_free_way(lem);
			lem->ways = copy;
			return (0);
		}
		lm_free_t_wroom_copy(copy);
	}
	return (0);
}
