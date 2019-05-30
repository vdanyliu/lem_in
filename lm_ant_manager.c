/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_ant_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 14:06:25 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/30 15:21:30 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ants	*lm_create_ants(long num)
{
	t_ants	*head;
	t_ants	*curr;

	head = NULL;
	curr = NULL;
	while (num)
	{
		if (!head)
		{
			head = (t_ants*)malloc(sizeof(t_ants));
			head->pre = NULL;
			head->ant_num = 1;
			curr = head;
			num--;
		}
		else
		{
			curr->next = (t_ants *) malloc(sizeof(t_ants));
			curr->next->ant_num = curr->ant_num + 1;
			curr->next->pre = curr;
			curr = curr->next;
			num--;
		}
	}
	curr->next = NULL;
	return (head);
}

static t_wroom	*lm_take_way(t_wroom *ways)
{
	t_wroom	*curr_choice;
	int 	i;

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

static void		lm_ants_ways(t_ants *ants_list, t_wroom *ways)
{
	while (ants_list)
	{
		ants_list->way = lm_take_way(ways);
		ants_list->curr = ants_list->way->list->room;
		ants_list->l_way =  ants_list->way->list;
		ants_list = ants_list->next;
	}
}

int 			lm_room_free(t_ants *ants, t_room *room, t_room *finish)
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
	int 	i;

	while (42)
	{
		g_turns++;
		i = 0;
		buff = ants;
		while (buff)
		{
			if (buff->l_way->next && lm_room_free(ants, buff->l_way->next->room, lem->finish))
			{
				write(1, " ", 1);
				buff->curr = buff->l_way->next->room;
				buff->l_way = buff->l_way->next;
				ft_printf("L%i-%s", buff->ant_num, buff->curr->name);
				i++;
			}
			buff = buff->next;
		}
		write(1, "\n", 1);
		if (!i)
		{
			g_turns--;
			return;
		}
	}
}

void		lm_ant_manager(t_lem *lem)
{
	g_turns = 0;
	lem->ants = lm_create_ants(lem->ants_numb);
	lm_ants_ways(lem->ants, lem->ways);
	lm_move_ants(lem->ants, lem);
}