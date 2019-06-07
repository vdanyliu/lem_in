/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_usefull2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:59:58 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/07 14:08:07 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				lm_way_len(t_wroom *ways)
{
	t_lroom	*curr_way;

	while (ways)
	{
		curr_way = ways->list;
		ways->len = 0;
		while (curr_way->next)
		{
			ways->len += 1;
			curr_way = curr_way->next;
		}
		ways->load = ways->len;
		ways = ways->nextlist;
	}
}

void				lm_free_way(t_lem *lem)
{
	t_wroom	*buff;
	t_wroom	*fre;
	t_lroom	*curr;
	t_lroom	*curr_free;

	buff = lem->ways;
	while (buff)
	{
		fre = buff;
		buff = buff->nextlist;
		curr = fre->list;
		while (curr)
		{
			curr_free = curr;
			curr = curr->next;
			free(curr_free);
		}
		free(fre);
	}
	lem->ways = NULL;
}

void				lm_free_bfs(t_bfs *bfs)
{
	t_bfs	*buff;

	while (bfs)
	{
		buff = bfs;
		bfs = bfs->next;
		free(buff);
	}
}

int					lm_check_stack(t_bfs *head, t_room *room, t_wroom *ways,
		t_lem *lem)
{
	t_lroom	*head_list;

	if (room == lem->finish)
		return (0);
	while (head)
	{
		if (head->room == room)
			return (1);
		head = head->next;
	}
	if (ways != 0)
	{
		while (ways)
		{
			head_list = ways->list;
			while (head_list)
			{
				if (room == head_list->room)
					return (1);
				head_list = head_list->next;
			}
			ways = ways->nextlist;
		}
	}
	return (0);
}

int					lm_calc_turns(t_lem *lem)
{
	int		i;
	t_ants	*ants;

	i = 0;
	lm_ants_ways(lem->ants, lem->ways, lem);
	ants = lem->ants;
	while (ants)
	{
		if (ants->way->load > i)
			i = ants->way->load;
		ants = ants->next;
	}
	return (i);
}
