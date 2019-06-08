/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_norme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:21:42 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/08 15:22:19 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				lm_mlx_print_room(t_room *room, int *img)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = room->x - 5;
	y = room->y - 5;
	dy = 0;
	while (dy < 10)
	{
		dx = 0;
		while (dx < 10)
		{
			img[((int)x + dx) + (((int)y + dy) * 4000)] = 0xff0000;
			dx++;
		}
		dy++;
	}
}

void					lm_print_s_f(t_lem *lem, int *img)
{
	lm_mlx_print_room(lem->start, img);
	lm_mlx_print_room(lem->finish, img);
}
