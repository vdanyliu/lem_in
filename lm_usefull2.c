/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_usefull2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:59:58 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/25 17:05:58 by vdanyliu         ###   ########.fr       */
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

int 				lm_check_stack(t_bfs *head, t_room *room)
{
	while (head)
	{
		if (head->room == room)
			return (1);
		head = head->next;
	}
	return (0);
}