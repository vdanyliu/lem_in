/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:14:31 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/07 14:20:18 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			lm_error(int i)
{
	ft_printf("ERROR\n");
	system("leaks -q Lem_in");
	exit(i);
}

t_ants			*lm_create_ants(long num)
{
	t_ants	*head;
	t_ants	*curr;

	head = NULL;
	curr = NULL;
	while (num)
	{
		if (!head)
		{
			head = (t_ants *)malloc(sizeof(t_ants));
			head->pre = NULL;
			head->ant_num = 1;
			curr = head;
			num--;
			continue;
		}
		curr->next = (t_ants *)malloc(sizeof(t_ants));
		curr->next->ant_num = curr->ant_num + 1;
		curr->next->pre = curr;
		curr = curr->next;
		num--;
	}
	curr->next = NULL;
	return (head);
}

t_bfs			*lm_find_parent(t_bfs *head, t_room *room)
{
	head = head->pre;
	while (head && head->room != room)
		head = head->pre;
	return (head);
}

void			lm_free_t_wroom(t_wroom *buff)
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
