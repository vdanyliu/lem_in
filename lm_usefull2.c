/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_usefull2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:59:58 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/28 18:26:00 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int 				lm_check_stack(t_bfs *head, t_room *room, t_wroom *ways, t_lem *lem)
{
	t_lroom	*head_list;

	if (room == lem->finish || room == lem->start)
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