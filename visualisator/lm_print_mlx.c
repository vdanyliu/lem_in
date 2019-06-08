/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_print_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:25:14 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/08 15:41:32 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					dda(t_room *room1, t_room *room2, int *img, int color)
{
	int		length;
	int		i;
	double	xy[2];
	double	xincrement;
	double	yincrement;

	length = abs(room2->x - room1->x);
	if (abs(room2->y - room1->y) > length)
		length = abs(room2->y - room1->y);
	xincrement = (double)(room2->x - room1->x) / (double)length;
	yincrement = (double)(room2->y - room1->y) / (double)length;
	xy[0] = room1->x + 0.5;
	xy[1] = room1->y + 0.5;
	i = 1;
	while (i++ <= length)
	{
		img[(int)xy[0] + ((int)xy[1] * 4000)] = color;
		xy[0] = xy[0] + xincrement;
		xy[1] = xy[1] + yincrement;
	}
}

static void				lm_to_link(t_room *room, t_lroom *list, int *img)
{
	while (list)
	{
		dda(room, list->room, img, 0xffffff);
		list = list->next;
	}
}

static void				lm_print_links(t_lem *lem, int *img)
{
	t_depth	*head;
	t_lroom	*de_list;

	head = lem->depth;
	while (head->next)
	{
		de_list = head->list;
		while (de_list)
		{
			lm_to_link(de_list->room, de_list->room->link, img);
			de_list = de_list->next;
		}
		head = head->next;
	}
}

static void				lm_print_ways(t_lem *lem, int *img)
{
	t_wroom	*ways;
	t_lroom	*list;
	int		color;

	color = 0x0000ff;
	ways = lem->ways;
	while (ways)
	{
		list = ways->list;
		while (list->next)
		{
			dda(list->room, list->next->room, img, color);
			list = list->next;
		}
		ways = ways->nextlist;
		if (color == 0xff0000)
			color = 0x0000ff;
		else if (color == 0x00ff00)
			color = 0xff0000;
		else if (color == 0x0000ff)
			color = 0x00ff00;
	}
}

void					lm_print_mlx(t_lem *lem)
{
	static void	*mlx_img = NULL;
	int			*img_data;
	int			a;
	int			b;
	int			c;

	mlx_img = mlx_new_image(lem->mlx->mlx_ptr, 4000, 3000);
	img_data = (int*)mlx_get_data_addr(mlx_img, &a, &b, &c);
	lm_print_links(lem, img_data);
	lm_print_ways(lem, img_data);
	lm_print_s_f(lem, img_data);
	mlx_put_image_to_window(lem->mlx->mlx_ptr, lem->mlx->win_ptr,
			mlx_img, 0, 0);
	mlx_do_sync(lem->mlx->mlx_ptr);
}
