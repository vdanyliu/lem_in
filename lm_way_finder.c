/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_way_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:35:50 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/28 18:52:21 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs 			*lm_find_parent(t_bfs *head, t_room *room)
{
	head = head->pre;
	while (head && head->room != room)
		head = head->pre;
	return (head);
}

static t_lroom	*lm_bfs_to_list(t_bfs *head)
{
	t_lroom	*head_list;
	t_lroom	*buff_list;

	head_list = NULL;
	while (head->next)
		head = head->next;
	while (head)
	{
		if (head_list == NULL)
		{
			head_list = (t_lroom*)malloc(sizeof(t_lroom));
			head_list->next = NULL;
			head_list->room = head->room;
			head = lm_find_parent(head, head->parent);
			continue ;
		}
		buff_list = head_list;
		head_list = (t_lroom*)malloc(sizeof(t_lroom));
		head_list->next = buff_list;
		head_list->room = head->room;
		head = lm_find_parent(head, head->parent);
	}
	return (head_list);
}

static t_wroom	*lm_bfs_to_way(t_bfs *head)
{
	t_wroom *way;
	way = (t_wroom*)malloc(sizeof(t_wroom));
	way->list = lm_bfs_to_list(head);
	way->nextlist = NULL;
	lm_free_bfs(head);
	lm_bfs_add_node(0, 0, 0, 1);
	return (way);
}

static	t_wroom	*lm_bfs(t_lem *lem, t_room *from, t_room *to)
{
	t_bfs	*head;
	t_bfs	*curr;
	t_lroom	*curr_link;

	head = lm_new_bfs_list(lem->start, from);
	curr = head;
	while (curr)
	{
		curr_link = curr->room->link;
		while (curr_link)
		{
			if (!lm_check_stack(head, curr_link->room, lem->ways, lem))
				lm_bfs_add_node(head, curr->room, curr_link->room, 0);
			if (curr_link->room == to)
				return (lm_bfs_to_way(head));
			curr_link = curr_link->next;
		}
		curr = curr->next;
	}
	return (0);
}

static t_wroom	*lm_find_way(t_lem *lem)
{
	t_lroom	*curr;
	t_wroom	*way;

	curr = lem->start->link;
	while (curr)
	{
		way = lm_bfs(lem, lem->start, lem->finish);
		if (way != 0)
			return (way);
		curr = curr->next;
	}
	return (0);
}

void		lm_debug_print_ways(t_wroom *ways)
{
	int i;

	i = 0;
	t_lroom	*curr;
	ft_printf("lm_debug_print_ways\n");
	while (ways)
	{
		curr = ways->list;
		ft_printf("way number %i :\t", i++);
		while (curr)
		{
			ft_printf("|Node%i| ", curr->room->num);
			curr = curr->next;
		}
		ft_printf("end of way\n");
		ways = ways->nextlist;
	}
}

void		lm_find_all_ways(t_lem *lem)
{
	t_wroom	*buff;
	t_wroom	*last;

	last = lem->ways;
	while ((buff = lm_find_way(lem)) != 0)
	{
		last->nextlist = buff;
		last = last->nextlist;
	}
}

void		lm_find_ways(t_lem *lem)
{
	lem->ways = lm_find_way(lem);
	if (lem->ways == 0)
	{
		ft_printf("ERROR\nCant find any ways\n");
		exit(0);
	}
	lm_find_all_ways(lem);
	lm_debug_print_ways(lem->ways);
}