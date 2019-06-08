/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_print_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:25:14 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/06/08 14:09:55 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			dda(t_room *room1, t_room *room2, int *img, int color)
{
	int length;
	int i;
	double x;
	double y;
	double xincrement;
	double yincrement;

	length = abs(room2->x - room1->x);
	if (abs(room2->y - room1->y) > length) length = abs(room2->y - room1->y);
	xincrement = (double)(room2->x - room1->x)/(double)length;
	yincrement = (double)(room2->y - room1->y)/(double)length;
	x = room1->x + 0.5;
	y = room1->y + 0.5;
	for (i = 1; i<= length;++i)
	{
		img[(int)x + ((int)y * 4000)] = color;
		x = x + xincrement;
		y = y + yincrement;
	}
}

static void				lm_to_link(t_room	*room, t_lroom *list, t_lem *lem, int *img)
{
	while (list)
	{
		dda(room, list->room, img, 0xffffff);
		list = list->next;
	}
}

static void				lm_print_links(t_lem *lem, int	*img)
{
	t_depth	*head;
	t_lroom	*de_list;

	head = lem->depth;
	while (head->next)
	{
		de_list = head->list;
		while (de_list)
		{
			lm_to_link(de_list->room, de_list->room->link, lem, img);
			de_list = de_list->next;
		}
		head = head->next;
	}
}

static void				lm_print_ways(t_lem *lem, int	*img)
{
	t_wroom	*ways;
	t_lroom	*list;
	int 	color;

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

static void 		lm_mlx_print_room(t_room *room, int *img)
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

static void			lm_print_s_f(t_lem *lem, int *img)
{
	lm_mlx_print_room(lem->start, img);
	lm_mlx_print_room(lem->finish, img);
}

void				lm_print_mlx(t_lem *lem)
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
	mlx_put_image_to_window(lem->mlx->mlx_ptr, lem->mlx->win_ptr, mlx_img, 0, 0);
	mlx_do_sync(lem->mlx->mlx_ptr);
}