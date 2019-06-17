/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:13:42 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/17 12:43:21 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					lm_parce_av(char *str)
{
	if (ft_strstr(str, "-help"))
	{
		ft_printf("usage : lem-in (arg) < map.txt\n'-' print number of lines\n"
			"'r' - print all rooms\n'w' - print all ways\n"
			"'b' - do without superposition\n"
			"'lem-in (arg) < map.txt | ./visu-hex' - to do visualisation\n");
		exit(0);
	}
	if (ft_strstr(str, "r"))
		g_rooms = 1;
	if (ft_strstr(str, "w"))
		g_ways = 1;
	if (ft_strstr(str, "b"))
		g_no_bahra = 1;
}

static void				lm_print_links(t_lem *lem)
{
	t_room	*room;
	t_lroom	*link;

	room = lem->rooms;
	while (room)
	{
		link = room->link;
		ft_printf("num = %i, name = %s links :\n", room->num, room->name);
		while (link->next)
		{
			ft_printf("|num = %i, name = %s|\t",
					link->room->num, link->room->name);
			link = link->next;
		}
		ft_printf("|num = %i, name = %s|\n", link->room->num, link->room->name);
		room = room->next;
	}
}

static void				lm_debug_print_ways(t_wroom *ways)
{
	int		i;
	t_lroom	*curr;

	i = 0;
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

void					lm_bonus_print(t_lem *lem)
{
	if (g_rooms == 1)
		lm_print_links(lem);
	if (g_ways == 1)
		lm_debug_print_ways(lem->ways);
}
