/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:54:59 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/30 14:52:19 by vdanyliu         ###   ########.fr       */
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

typedef struct		s_wroom
{
	int				len;
	int 			load;
	t_lroom			*list;
	struct s_wroom	*nextlist;
}					t_wroom;

typedef struct			s_gnl_buff
{
	char 				*gnl;
	struct s_gnl_buff	*next;
}						t_gnl_buff;

typedef struct		s_bfs
{
	t_room			*parent;
	t_room			*room;
	struct s_bfs	*next;
	struct s_bfs	*pre;
}					t_bfs;

typedef struct		s_ants
{
	int 			ant_num;
	t_room			*curr;
	t_wroom			*way;
	t_lroom			*l_way;
	struct s_ants	*next;
	struct s_ants	*pre;
}					t_ants;

typedef struct		s_lem_in
{
	long			ants_numb;
	t_room			*rooms;
	t_room			*start;
	t_room			*finish;
	t_gnl_buff		*gnl;
	t_wroom			*ways;
	t_ants			*ants;
}					t_lem;

int 				g_turns;
void				lm_error(int i);
t_lem				*lm_create_lem(void);
void				lm_add(char *gnl, t_lem *lem, int mod);
void				lm_parce_ants(char *gnl, long *ant_num);
int					all_is_num(char *str);
void				lm_parce_rooms(char *gnl, t_lem *lem);
void				lm_parce_link(char *str, t_lem *lem);
void				lm_free_split(char **str);
t_room				*lm_last_room(t_lem *lem);
void				lm_add_gnl(t_gnl_buff *gnl_lst, char *gnl);
void				lm_print_gnl(t_gnl_buff *gnl_lst);
void				lm_find_ways(t_lem *lem);
t_bfs				*lm_new_bfs_list(t_room *parent, t_room *curr);
void				lm_bfs_add_node(t_bfs *head, t_room *from, t_room *room, int i);
void				lm_free_bfs(t_bfs *bfs);
int 				lm_check_stack(t_bfs *head, t_room *room, t_wroom *ways, t_lem *lem);
void				lm_free_way(t_lem *lem);
int 				lm_bahram(t_lem *lem);
t_wroom				*lm_find_way(t_lem *lem);
void				lm_create_link(t_room *room1, t_room *room2);
void				lm_print_links(t_lem *lem);
void				lm_debug_print_ways(t_wroom *ways);
void				lm_way_len(t_wroom *ways);
void				lm_ant_manager(t_lem *lem);
int 				lm_room_free(t_ants *ants, t_room *room, t_room *finish);

#endif
