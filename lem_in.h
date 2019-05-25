/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:54:59 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/25 17:46:40 by vdanyliu         ###   ########.fr       */
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

typedef struct		s_lem_in
{
	long			ants_numb;
	t_room			*rooms;
	t_room			*start;
	t_room			*finish;
	t_gnl_buff		*gnl;
	t_wroom			*ways;
}					t_lem;

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
void				lm_cut_start_links(t_lem *lem);
void				lm_find_ways(t_lem *lem);
t_bfs				*lm_new_bfs_list(t_room *parent, t_room *curr);
void				lm_bfs_add_node(t_bfs *head, t_room *from, t_room *room, int i);
void				lm_free_bfs(t_bfs *bfs);
int 				lm_check_stack(t_bfs *head, t_room *room);

#endif
