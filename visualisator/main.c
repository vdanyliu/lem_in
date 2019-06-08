/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:31:22 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/08 13:25:13 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static int			key_release(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
		exit(0);
	return (0);
}

static int			closeprog(void *param)
{
	(void)param;
	exit(0);
}

static void			fdf_mlx_manipulation(t_mlx_ptr *mlx)
{
	mlx_hook((mlx)->win_ptr, 17, 0, closeprog, (void *)0);
	mlx_hook((mlx)->win_ptr, 2, 0, key_release, (void *)mlx);
}


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
			return ;
		if (!ft_strcmp(gnl, "ERROR"))
			lm_error(66);
		else if (*gnl == '#')
			lm_hesh_parcer(gnl, lem);
		else
			lm_add(gnl, lem, 0);
	}
	if (!lem->start || !lem->finish)
		lm_error(11);
	free(gnl);
}

void			lm_calc_coord(t_depth *head)
{
	t_lroom *list;
	int 	i;

	while (head)
	{
		list = head->list;
		i = 1;
		while (list)
		{
			list->room->x = (20 * i++);
			list->room->y = head->depth * 20;
			list = list->next;
		}
		head = head->next;
	}
}

void			lm_print_coord(t_lem *lem)
{
	t_room	*curr;

	curr = lem->rooms;
	while (curr)
	{
		ft_printf("room %i x = %i y = %i\n", curr->num, curr->x, curr->y);
		curr = curr->next;
	}
}

int				main(int ac, char **av)
{
	t_lem	*lem;

	lem = lm_create_lem();
	lm_parcer(lem);
	lm_calc_depth(lem);
	lm_calc_coord(lem->depth);
	lm_print_coord(lem); //debug
	lem->mlx = mlx_initiation();
	//lm_print_mlx(lem);
	lm_find_ways(lem);
	//lm_ant_manager(lem);
	if (*lem->gnl->next->gnl == '#' && *(lem->gnl->next->gnl + 1) != '#' &&
	ac > 1 && av[1][0] == '-')
	{
		ft_printf("%s\n", lem->gnl->next->gnl);
		ft_printf("#Here is the number of lines by my lem: %i\n", g_turns);
	}
	fdf_mlx_manipulation(lem->mlx);
	mlx_loop(lem->mlx->mlx_ptr);
	return (0);
}
