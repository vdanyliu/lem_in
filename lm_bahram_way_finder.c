/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bahram_way_finder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:46:19 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/06 20:40:58 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room				*lm_next_room_in_way(t_room *room)
{
	t_lroom	*curr;

	if (room->belong_to == 0)
		return (0);
	curr = room->belong_to->list;
	while (curr->next)
	{
		if (curr->room == room)
			return (curr->next->room);
		curr = curr->next;
	}
	return (0);
}

t_room				*lm_pre_room_in_way(t_room *room)
{
	t_lroom	*curr;

	curr = room->belong_to->list;
	while (curr->next)
	{
		if (curr->next->room == room)
			return (curr->room);
		curr = curr->next;
	}
	return (0);
}

static int			lm_flag_select(t_room *room, t_bfs *head, t_bfs *pre)
{
	while (head)
	{
		if (head->room == room && head->flags != 1)
			return (-1);
		head = head->next;
	}
	if (pre && pre->flags == 1 && lm_pre_room_in_way(pre->room) != room)
		return (-1);
	if (pre && pre->flags == 0 && lm_next_room_in_way(pre->room) == room)
		return (-1);
	if (room->belong_to)
	{
		if (pre->pre == 0)
			return (-1);
		if (room->belong_to != pre->room->belong_to)
			return (1);
	}
	return (0);
}

static void			lm_bfs_add_node_bahram(t_bfs *head, t_room *from,
		t_room *room, int flag)
{
	if (flag < 0)
		return ;
	while (head->next)
		head = head->next;
	head->next = lm_new_bfs_list(from, room);
	head->next->flags = flag;
	head->next->pre = head;
}

t_wroom				*lm_find_way_bahram(t_lem *lem)
{
	t_bfs	*head;
	t_bfs	*curr;
	t_lroom	*curr_link;
	int		flag;

	head = lm_new_bfs_list(lem->start, lem->start);
	curr = head;
	while (curr)
	{
		curr_link = curr->room->link;
		while (curr_link)
		{
			flag = lm_flag_select(curr_link->room, head, curr);
			lm_bfs_add_node_bahram(head, curr->room, curr_link->room, flag);
			if (curr_link->room == lem->finish && flag != -1)
				return (lm_bfs_to_way(head));
			curr_link = curr_link->next;
		}
		curr = curr->next;
	}
	return (0);
}
