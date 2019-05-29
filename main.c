/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:31:22 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/29 14:03:54 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			lm_parce_ants(char *gnl, long *ant_num)
{
	long	i;
	if (*gnl == '0' || !all_is_num(gnl))
		lm_error(66);
	i = ft_atoi(gnl);
	if (i <= 0)
		lm_error(66);
	*ant_num = i;
}

void			lm_add(char *gnl, t_lem *lem, int mod)
{
	static int room_open = 0;

	if (mod >= 2)
	{
		room_open = 1;
		return ;
	}
	if (lem->ants_numb == 0)
		lm_parce_ants(gnl, &(lem->ants_numb));
	else if (room_open == 0)
		lm_parce_rooms(gnl, lem);
	else
		lm_parce_link(gnl, lem);
//	ft_printf("%s\n", gnl);
	lm_add_gnl(lem->gnl, gnl);
}

static void		lm_hesh_parcer(char *gnl, t_lem *lem)
{
	if (ft_strstr(gnl, "##start") && ft_strlen(gnl) == ft_strlen("##start"))
	{
		if (lem->start != NULL)
			lm_error(66);
		//ft_printf("%s\n", gnl);
		//free(gnl);
		lm_add_gnl(lem->gnl, gnl);
		get_next_line(0, &gnl);
		lm_add(gnl, lem, 0);
		lem->start = lm_last_room(lem);
	}
	else if (ft_strstr(gnl, "##end") && ft_strlen(gnl) == ft_strlen("##end"))
	{
		if (lem->finish != NULL)
			lm_error(66);
//		ft_printf("%s\n", gnl);
//		free(gnl);
		lm_add_gnl(lem->gnl, gnl);
		get_next_line(0, &gnl);
		lm_add(gnl, lem, 0);
		lem->finish = lm_last_room(lem);
	}
	else
		lm_add_gnl(lem->gnl, gnl);
//		ft_printf("%s\n", gnl);
	//free(gnl);
}

static void 	lm_parcer(t_lem *lem)
{
	char	*gnl;

	while(get_next_line(0, &gnl) > 0)
	{

		if (*gnl == 0 || *gnl == 'L')
			lm_error(0);
		else if (*gnl == '#')
			lm_hesh_parcer(gnl, lem);
		else
		{
			lm_add(gnl, lem, 0);   // 3 мод
//			free(gnl);
		}
	}
	if (!lem->start || !lem->finish)
		lm_error(11);
	free(gnl);
	ft_printf("END OF PARCER\n");

}


void			lm_print_links(t_lem *lem) //debug
{
	t_room	*room;
	t_lroom	*link;

	room = lem->rooms;
	while(room)
	{
		link = room->link;
		ft_printf("num = %i, name = %s links :\n", room->num, room->name);
		while(link->next)
		{
			ft_printf("|num = %i, name = %s|\t", link->room->num, link->room->name);
			link = link->next;
		}
		ft_printf("|num = %i, name = %s|\n", link->room->num, link->room->name);
		room = room->next;
	}
}

void			lm_print_links_head(t_lem *lem) // debug
{
	t_lroom	*head;
	t_lroom	*links;
	t_room	*room;

	head = lem->rooms->link;
	while(head)
	{
		room = head->room;
		links = room->link;
		ft_printf("link of head head(%i)\tlinks = ", head->room->num);
		while(links)
		{
			ft_printf("| num = %i|\t", links->room->num);
			links = links->next;
		}
		head = head->next;
		ft_printf("\n");
	}
	ft_printf("end of start links\n");
}

static void		lm_initiation(t_lem **lem_in)
{
	*lem_in = lm_create_lem();
	lm_parcer(*lem_in);
	lm_print_gnl((*lem_in)->gnl);
}

int				main(void)
{
	t_lem	*lem_in;

	lem_in = NULL;
	lm_initiation(&lem_in);
	//lm_print_links(lem_in); //debug
	lm_cut_start_links(lem_in);
	//lm_print_links_head(lem_in); //debug
	lm_find_ways(lem_in);
	return (0);
}
