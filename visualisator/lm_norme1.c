/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_norme1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:50:25 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/08 15:53:05 by vdanyliu         ###   ########.fr       */
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

void				fdf_mlx_manipulation(t_mlx_ptr *mlx)
{
	mlx_hook((mlx)->win_ptr, 17, 0, closeprog, (void *)0);
	mlx_hook((mlx)->win_ptr, 2, 0, key_release, (void *)mlx);
}

void				lm_parce_ants(char *gnl, long *ant_num)
{
	long	i;

	if (*gnl == '0' || !all_is_num(gnl))
		lm_error(66);
	i = ft_atoi(gnl);
	if (i <= 0)
		lm_error(66);
	*ant_num = i;
}
