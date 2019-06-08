/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_depth_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:43:22 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/08 15:16:00 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lroom	*lm_create_list(t_lroom *links)
{
	t_lroom	*head;
	t_lroom	*curr;

	head = NULL;
	while (links)
	{
		if (links->room->depth == -1)
		{
			if (!head)
			{
				head = getlroom(links);
				curr = head;
			}
			else
			{
				curr->next = (t_lroom*)malloc(sizeof(t_lroom));
				curr->next->room = links->room;
				curr->next->room->depth = 10;
				curr->next->next = NULL;
				curr = curr->next;
			}
		}
		links = links->next;
	}
	return (head);
}

static t_lroom	*lm_add_list(t_lroom *head, t_lroom *room_link)
{
	t_lroom	*curr;

	if (!head)
	{
		head = lm_create_list(room_link);
		return (head);
	}
	curr = head;
	while (curr->next)
		curr = curr->next;
	curr->next = lm_create_list(room_link);
	return (head);
}

static t_depth	*lm_add_depth(t_lroom *list, int i)
{
	t_depth	*head;

	head = (t_depth*)malloc(sizeof(t_depth));
	head->depth = i;
	head->next = 0;
	head->list = 0;
	while (list)
	{
		head->list = lm_add_list(head->list, list->room->link);
		list = list->next;
	}
	return (head);
}

int				lm_mark_depth(t_lroom *curr, int i)
{
	int	j;

	j = 0;
	while (curr)
	{
		curr->room->depth = i;
		curr = curr->next;
		j++;
	}
	return (j);
}

void			lm_calc_depth(t_lem *lem)
{
	t_depth	*head;
	t_depth	*curr;

	head = (t_depth*)malloc(sizeof(t_depth));
	head->next = NULL;
	head->depth = 1;
	head->list = (t_lroom*)malloc(sizeof(t_lroom));
	head->list->room = lem->start;
	head->list->next = NULL;
	head->count = 1;
	lem->start->depth = 0;
	curr = head;
	while (curr->list)
	{
		curr->next = lm_add_depth(curr->list, (curr->depth + 1));
		curr->next->count = lm_mark_depth(curr->next->list, (curr->depth + 1));
		curr = curr->next;
	}
	lem->depth = head;
}
