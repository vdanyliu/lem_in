/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:31:22 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/22 19:19:10 by vdanyliu         ###   ########.fr       */
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
	ft_printf("%s\n", gnl);
}

static void		lm_hesh_parcer(char *gnl, t_lem *lem)
{
	if (ft_strstr(gnl, "##start") && ft_strlen(gnl) == ft_strlen("##start"))
	{
		if (lem->start != NULL)
			lm_error(66);
		ft_printf("%s\n", gnl);
		free(gnl);
		get_next_line(g_fd, &gnl);
		lm_add(gnl, lem, 0);
		lem->start = lm_last_room(lem);
	}
	else if (ft_strstr(gnl, "##end") && ft_strlen(gnl) == ft_strlen("##end"))
	{
		if (lem->finish != NULL)
			lm_error(66);
		ft_printf("%s\n", gnl);
		free(gnl);
		get_next_line(g_fd, &gnl);
		lm_add(gnl, lem, 0);
		lem->finish = lm_last_room(lem);
	}
	else
		ft_printf("%s\n", gnl);
	free(gnl);
}

static void 	lm_parcer(t_lem *lem)
{
	char	*gnl;

	while(get_next_line(g_fd, &gnl) > 0)
		if (*gnl == 0 || *gnl == 'L')
			lm_error(0);
		else if (*gnl == '#')
			lm_hesh_parcer(gnl, lem);
		else
		{
			lm_add(gnl, lem, 0);   // 3 мод
			free(gnl);
		}
	if (!lem->start || !lem->finish)
		lm_error(11);
	ft_printf("END OF PARCER\n");
}

static void		lm_initiation(t_lem **lem_in)
{
	*lem_in = lm_create_lem();
	lm_parcer(*lem_in);
}

int				main(void)
{
	t_lem	*lem_in;

	g_fd = 0;
	lem_in = NULL;
	lm_initiation(&lem_in);
	return (0);
}
