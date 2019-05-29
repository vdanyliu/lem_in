/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bahram.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:51:20 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/29 20:49:23 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int 		lm_same(t_room *room, t_lroom *way)
{
	while (way->next)
	{
		if (way->room == room)
			return (1);
		way = way->next;
	}
	return (0);
}

static t_lroom		*lm_del_link(t_lroom *head, t_room *room)
{
	t_lroom *buff;
	t_lroom	*pre;

	if ((head)->room == room)
	{
		buff = head;
		head = (head)->next;
		free(buff);
		return (head);
	}
	buff = head;
	while (buff->room != room)
	{
		pre = buff;
		buff = buff->next;
	}
	pre->next = buff->next;
	free(buff);
	return (head);
}

static int 		lm_check_same(t_wroom *all, t_wroom *way, t_lem *lem)
{
	t_lroom	*curr;
	t_lroom	*next;
	while (all)
	{
		curr = all->list;
		while (curr && curr->next)
		{
			curr = curr->next;
			next = curr->next;
			if (lm_same(curr->room, way->list))
			{
				next->room->link = lm_del_link((next->room->link), curr->room);
//				lm_del_link(&(next->room->link), curr->room);
				return (1);
			}
			curr = curr->next;
		}
		all = all->nextlist;
	}
	return (0);
}

static void		lm_change_graph_dir(t_wroom *ways)
{
	t_lroom	*curr_way;

	while (ways)
	{
		curr_way = ways->list;
		while (curr_way->next)
		{
			curr_way->room->link = lm_del_link(curr_way->room->link, curr_way->next->room);
			curr_way = curr_way->next;
		}
		ways = ways->nextlist;
	}
}

static int 		lm_link_check(t_room *room1, t_room *room2)
{
	t_lroom *links;

	links = room2->link;
	while (links)
	{
		if (links->room == room1)
			return (1);
		links = links->next;
	}
	return (0);
}

static void		lm_back_graph_dir(t_wroom *ways)
{
	t_lroom	*curr_way;

	while (ways)
	{
		curr_way = ways->list;
		while (curr_way->next)
		{
			if (lm_link_check(curr_way->room, curr_way->next->room))
				lm_create_link(curr_way->room, curr_way->next->room);
			curr_way = curr_way->next;
		}
		ways = ways->nextlist;
	}
}

void				lm_free_way_bah(t_wroom *way)
{
	t_lroom	*curr;
	t_lroom	*curr_free;

		curr = way->list;
		while (curr)
		{
			curr_free = curr;
			curr = curr->next;
			free(curr_free);
		}
		free(way);
}

int 			lm_bahram(t_lem *lem)
{
	t_wroom	*way;
	t_wroom	*all;
	int		i;

	i = 0;
	lm_change_graph_dir(lem->ways);
	all = lem->ways;
	lem->ways = NULL;
	way = lm_find_way(lem);
	if (way == 0)
	{
		lem->ways = all;
		lm_back_graph_dir(lem->ways);
		return (0);
	}
//	ft_printf("\nSTART\n");
//	lm_print_links(lem);
//	ft_printf("\nEND\n\n\n");
	lem->ways = all;
	i = lm_check_same(lem->ways, way, lem);
	lm_back_graph_dir(lem->ways);
	lm_free_way_bah(way);
	return (i);
}