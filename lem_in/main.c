/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:31:22 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/13 19:11:27 by vdanyliu         ###   ########.fr       */
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
	lm_add_gnl(lem->gnl, gnl);
}

static void		lm_hesh_parcer(char *gnl, t_lem *lem)
{
	if (ft_strstr(gnl, "##start") && ft_strlen(gnl) == ft_strlen("##start"))
	{
		if (lem->start != NULL)
			lm_error(66);
		lm_add_gnl(lem->gnl, gnl);
		get_next_line(0, &gnl);
		lm_add(gnl, lem, 0);
		lem->start = lm_last_room(lem);
	}
	else if (ft_strstr(gnl, "##end") && ft_strlen(gnl) == ft_strlen("##end"))
	{
		if (lem->finish != NULL)
			lm_error(66);
		lm_add_gnl(lem->gnl, gnl);
		get_next_line(0, &gnl);
		lm_add(gnl, lem, 0);
		lem->finish = lm_last_room(lem);
	}
	else
		lm_add_gnl(lem->gnl, gnl);
}

static void		lm_parcer(t_lem *lem)
{
	char	*gnl;

	while (get_next_line(0, &gnl) > 0)
	{
		if (*gnl == 0 || *gnl == 'L')
			lm_error(0);
		else if (*gnl == '#')
			lm_hesh_parcer(gnl, lem);
		else
		{
			lm_add(gnl, lem, 0);
		}
	}
	if (!lem->start || !lem->finish)
		lm_error(11);
	free(gnl);
}

int				main(int ac, char **av)
{
	t_lem	*lem;

	lem = lm_create_lem();
	ac != 1 ? lm_parce_av(av[1]) : 0;
	lm_parcer(lem);
	lm_find_ways(lem);
	lm_print_gnl((lem)->gnl);
	lm_ant_manager(lem);
	if (ac > 1 && av[1][0] == '-')
	{
		if (*lem->gnl->next->gnl == '#' && *(lem->gnl->next->gnl + 1) != '#')
			ft_printf("%s\n", lem->gnl->next->gnl);
		ft_printf("#Here is the number of lines by my lem: %i\n", g_turns);
	}
	lm_bonus_print(lem);
	return (0);
}
