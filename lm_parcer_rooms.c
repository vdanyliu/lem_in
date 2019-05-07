/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parcer_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:01:17 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/07 19:31:39 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_same(t_room *buff, t_room *room)
{
	char *str1;
	char *str2;
	if (buff->x == room->x && buff->y == room->y)
		lm_error(67);
	str1 = buff->name;
	str2 = room->name;
	while (*str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (!*str1 && !*str2)
		lm_error(67);
}

static void		lm_add_room_list(t_room *room, t_lem *lem)
{
	static int	i = 0;
	t_room *buff;
	if (lem->rooms == NULL)
	{
		lem->rooms = room;
		room->num = i++;
	}
	else
	{
		buff = lem->rooms;
		while (buff->next)
		{
			check_same(buff, room);
			buff = buff->next;
		}
		check_same(buff, room);
		buff->next = room;
		room->num = i;
	}
}

static void		*lm_create_room(char *name, char *x, char *y)
{
	t_room	*room;

	room = (t_room*)malloc(sizeof(t_room));
	room->x = ft_atoi(x);
	room->y = ft_atoi(y);
	room->name = ft_strdup(name);
	room->next = NULL;
	room->link = NULL;
	return (room);
}

void			lm_parce_rooms(char *gnl, t_lem *lem)
{
	char	**split;
	t_room	*room;

	split = ft_strsplit(gnl, ' ');
	if (split[0] == 0 || split[1] == 0 || split[2] == 0 || split[3] != 0)
	{
		lm_add(0, 0, 2);
		lm_parce_link(gnl, lem);
		return ;
	}
	if (!all_is_num(split[1]) || !all_is_num(split[2]))
		lm_error(66);
	room = lm_create_room(split[0], split[1], split[2]);
	lm_add_room_list(room, lem);
	lm_free_split(split);
}