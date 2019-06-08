/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ini.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:09:53 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/07 19:11:34 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_mlx_ptr	*mlx_ptr_init(void)
{
	t_mlx_ptr	*mlx_ptrs;

	mlx_ptrs = (t_mlx_ptr*)(malloc)(sizeof(*mlx_ptrs));
	mlx_ptrs->mlx_ptr = mlx_init();
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->mlx_ptr, 4000, 3000, "Filler");
	return (mlx_ptrs);
}
t_mlx_ptr			*mlx_initiation(void)
{
	t_mlx_ptr		*mlx;

	mlx = mlx_ptr_init();
	return (mlx);
}
