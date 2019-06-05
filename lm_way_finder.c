/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_way_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:35:50 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/05 19:53:40 by vdanyliu         ###   ########.fr       */
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
			head_list->pre = NULL;
			head_list->room = head->room;
			head = lm_find_parent(head, head->parent);
			continue ;
		}
		buff_list = head_list;
		head_list = (t_lroom*)malloc(sizeof(t_lroom));
		head_list->next = buff_list;
		buff_list->pre = head_list;
		head_list->room = head->room;
		head = lm_find_parent(head, head->parent);
	}
	return (head_list);
}

t_wroom	*lm_bfs_to_way(t_bfs *head)
{
	t_wroom *way;
	way = (t_wroom*)malloc(sizeof(t_wroom));
	way->list = lm_bfs_to_list(head);
	way->nextlist = NULL;
	way->len = 0;
	way->load = 0;
	lm_free_bfs(head);
	lm_bfs_add_node(0, 0, 0, 1);
	return (way);
}

static t_wroom	*lm_bfs(t_lem *lem, t_room *from, t_room *to)
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
	lm_free_bfs(head);
	lm_bfs_add_node(0, 0, 0, 1);
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
		ft_printf("way number %i len = %i: ", i++, ways->len);
		while (curr)
		{
			ft_printf("|%s| ", curr->room->name);
			curr = curr->next;
		}
		ft_printf("end of way\n");
		ways = ways->nextlist;
	}
}

void		lm_free_t_wroom(t_wroom *buff)
{
	t_lroom	*curr;
	t_lroom	*pre;

	curr = buff->list;
	while (curr)
	{
		pre = curr;
		curr = curr->next;
		free(pre);
	}
	free(buff);
}

void		lm_find_all_ways(t_lem *lem)
{
	t_wroom	*buff;
	t_wroom	*last;
	int 	pre;

	last = lem->ways;
	while ((buff = lm_bfs(lem, lem->start, lem->finish)) != 0)
	{
		pre = lm_calc_turns(lem);
		ft_printf("turn calc = %i\n", pre);
		last->nextlist = buff;
		if (pre <= lm_calc_turns(lem))
		{
			lm_free_t_wroom(buff);
			last->nextlist = NULL;
			break ;
		}
		last = last->nextlist;
	}
	lm_bahram(lem);
}

void		lm_find_ways(t_lem *lem)
{
	lem->ways = lm_bfs(lem, lem->start, lem->finish);
	if (lem->ways == 0)
	{
		ft_printf("ERROR\nCant find any ways\n");
		exit(0);
	}
	lem->ants = lm_create_ants(lem->ants_numb);
	lm_way_len(lem->ways);
	if (lem->ways->len == 1)
	{
		lm_ants_ways(lem->ants, lem->ways, lem);
		return;
	}
	lm_find_all_ways(lem);
}