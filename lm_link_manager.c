/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_link_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:31:52 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/25 15:15:09 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lm_cut_start_links(t_lem *lem)
{
	t_room	*curr;
	t_lroom	*links;
	t_lroom	*currlinks;
	t_lroom	*buff;

	links = lem->start->link;
	while (links)
	{
		curr = links->room;
		currlinks = curr->link;
		buff = currlinks;
		while (currlinks->room->num != lem->start->num)
			currlinks = currlinks->next;
		while (buff->next != currlinks && buff != currlinks)
			buff = buff->next;
		if (buff == currlinks)
			curr->link = buff->next;
		else
			buff->next = currlinks->next;
		free(currlinks);
		links = links->next;
	}
}
