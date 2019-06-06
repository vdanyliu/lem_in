/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bahram_way_fixer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:19:12 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/06 16:46:13 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lroom	*lm_found_first_same_down(t_lroom *l_same_down, t_room *room)
{
	while (l_same_down->room != room)
		l_same_down = l_same_down->pre;
	return (l_same_down);
}

static t_lroom	*lm_found_last_same_up(t_lroom *f_same_up, t_lroom *l_same_down)
{
	while (f_same_up->next->room == l_same_down->pre->room)
	{
		f_same_up = f_same_up->next;
		l_same_down = l_same_down->pre;
	}
	return (f_same_up);
}

static t_lroom	*lm_found_same_up(t_wroom *head, t_room *room)
{
	t_lroom	*curr;

	while (head)
	{
		curr = head->list;
		while (curr)
		{
			if (curr->room == room)
				return (curr);
			curr = curr->next;
		}
		head = head->nextlist;
	}
	ft_printf("no same room in lm_found_same_up\nABOARD\n");
	exit(66);
}

static void	lm_free_lway(t_lroom *from, t_lroom *to)
{
	t_lroom	*buff;

	while (from != to)
	{
		buff = from;
		from = from->next;
		free(buff);
	}
}

void	lm_bahram_fix_ways(t_lem *lem)
{
	t_lroom	*l_same_up;
	t_lroom	*f_same_up;
	t_lroom	*l_same_down;
	t_lroom	*f_same_down;

	g_debug = 0;
	while ((l_same_down = lm_check_way_same_node(lem->ways, lem)))
	{
		f_same_up = lm_found_same_up(lem->ways, l_same_down->room);
		l_same_up = lm_found_last_same_up(f_same_up, l_same_down);
		f_same_down = lm_found_first_same_down(l_same_down, l_same_up->room);
		f_same_up->pre->next = l_same_down;
		l_same_down->pre = f_same_up->pre;
		f_same_down->pre->next = l_same_up;
		l_same_up ->pre = f_same_down->pre;
		lm_free_lway(f_same_up, l_same_up);
		lm_free_lway(f_same_down, l_same_down);
		g_debug++;
	}
}
