/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:24:23 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/23 15:30:36 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			lm_add_gnl(t_gnl_buff *gnl_lst, char *gnl)
{
	static t_gnl_buff	*curr = NULL;

	if (!curr)
	{
		gnl_lst->gnl = gnl;
		curr = gnl_lst;
	}
	else
	{
		curr->next = (t_gnl_buff*)malloc(sizeof(t_gnl_buff));
		curr = curr->next;
		curr->next = NULL;
		curr->gnl = gnl;
	}
}

void			lm_print_gnl(t_gnl_buff *gnl_lst)
{
	while (gnl_lst)
	{
		ft_printf("%s\n", gnl_lst->gnl);
		gnl_lst = gnl_lst->next;
	}
}
