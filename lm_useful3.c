/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_useful3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:13:24 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/06 15:29:24 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lroom			*lm_check_way_same_node(t_wroom *head, t_lem *lem)
{
	t_wroom	*curr_wroom;
	t_lroom	*curr_lroom;
	t_lroom	*down_lroom;

	while (head->nextlist)
	{
		curr_lroom = head->list;
		while (curr_lroom)
		{
			curr_wroom = head->nextlist;
			while (curr_wroom)
			{
				down_lroom = curr_wroom->list;
				while (down_lroom)
				{
					if (down_lroom->room == curr_lroom->room && down_lroom->room != lem->start && down_lroom->room != lem->finish)
						return (down_lroom);
					down_lroom = down_lroom->next;
				}
				curr_wroom = curr_wroom->nextlist;
			}
			curr_lroom = curr_lroom->next;
		}
		head = head->nextlist;
	}
	return (0);
}

void			lm_add_way(t_wroom *origin, t_wroom *to_end)
{
	while (origin->nextlist)
		origin = origin->nextlist;
	origin->nextlist = to_end;
}

static t_lroom	*lm_copy_lway(t_lroom *origin)
{
	t_lroom	*head;
	t_lroom	*curr;

	head = NULL;
	while (origin)
	{
		if (head == NULL)
		{
			head = (t_lroom*)malloc(sizeof(t_lroom));
			head->next = NULL;
			head->pre = NULL;
			head->room = origin->room;
			curr = head;
			origin = origin->next;
			continue ;
		}
		curr->next = (t_lroom*)malloc(sizeof(t_lroom));
		curr->pre = curr;
		curr = curr->next;
		curr->room = origin->room;
		curr->next = NULL;
		origin = origin->next;
	}
	return (head);
}

t_wroom			*lm_copy_way(t_wroom *origin)
{
	t_wroom *head;
	t_wroom *curr;

	head = NULL;
	while (origin)
	{
		if (head == NULL)
		{
			head = (t_wroom*)malloc(sizeof(t_wroom));
			head->len = origin->len;
			head->load = origin->load;
			head->list = lm_copy_lway(origin->list);
			head->nextlist = NULL;
			curr = head;
			origin = origin->nextlist;
			continue ;
		}
		curr->nextlist = (t_wroom*)malloc(sizeof(t_wroom));
		curr = curr->nextlist;
		curr->len = origin->len;
		curr->load = origin->load;
		curr->list = lm_copy_lway(origin->list);
		curr->nextlist = NULL;
		origin = origin->nextlist;
	}
	return (head);
}
