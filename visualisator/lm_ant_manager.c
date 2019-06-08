/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_ant_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 14:06:25 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/07 15:20:22 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_wroom	*lm_take_way(t_wroom *ways)
{
	t_wroom	*curr_choice;
	int		i;

	curr_choice = ways;
	i = curr_choice->load;
	ways = ways->nextlist;
	while (ways)
	{
		if (i > ways->load)
			curr_choice = ways;
		ways = ways->nextlist;
	}
	curr_choice->load += 1;
	return (curr_choice);
}

void			lm_ants_ways(t_ants *ants_list, t_wroom *ways, t_lem *lem)
{
	lm_way_len(lem->ways);
	while (ants_list)
	{
		ants_list->way = lm_take_way(ways);
		ants_list->curr = ants_list->way->list->room;
		ants_list->l_way = ants_list->way->list;
		ants_list = ants_list->next;
	}
}

int				lm_room_free(t_ants *ants, t_room *room, t_room *finish)
{
	while (ants)
	{
		if (ants->curr == room && room != finish)
			return (0);
		ants = ants->next;
	}
	return (1);
}

static void		lm_move_ants(t_ants *ants, t_lem *lem)
{
	t_ants	*buff;
	int		i;

	while (42)
	{
		i = 0;
		buff = ants;
		while (buff)
		{
			if (buff->l_way->next && lm_room_free(ants, buff->l_way->next->room,
					lem->finish))
			{
				buff->curr = buff->l_way->next->room;
				buff->l_way = buff->l_way->next;
				i++ != 0 ? ft_printf(" L%i-%s", buff->ant_num, buff->curr->name)
				: ft_printf("L%i-%s", buff->ant_num, buff->curr->name);
			}
			buff = buff->next;
		}
		if (!i)
			return ;
		g_turns++;
		write(1, "\n", 1);
	}
}

void			lm_ant_manager(t_lem *lem)
{
	g_turns = 0;
	lm_ants_ways(lem->ants, lem->ways, lem);
	lm_move_ants(lem->ants, lem);
}
