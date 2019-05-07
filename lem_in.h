/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:54:59 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/07 19:31:39 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/src/libft.h"

typedef struct		s_room
{
	int 			num;
	int				x;
	int				y;
	char			*name;
	struct s_room	*next;
	struct s_lroom	*link;
}					t_room;

typedef struct		s_lroom
{
	t_room			*room;
	struct s_lroom	*next;
}					t_lroom;

typedef struct		s_lem_in
{
	long			ants_numb;
	t_room			*rooms;
	t_room			*start;
	t_room			*finish;
}					t_lem;

int 				g_fd;
void				lm_error(int i);
t_lem				*lm_create_lem(void);
void				lm_add(char *gnl, t_lem *lem, int mod);
void				lm_parce_ants(char *gnl, long *ant_num);
int					all_is_num(char *str);
void				lm_parce_rooms(char *gnl, t_lem *lem);
void				lm_free_split(char **str);

#endif
