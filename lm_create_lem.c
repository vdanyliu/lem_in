/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_create_lem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:35:40 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/05/23 15:24:33 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//t_lem		*lm_create_lem(void)
//{
//	t_lem	*head;
//
//	head = (t_lem*)malloc(sizeof(t_lem));
//	head->ants_numb = 0;
//	head->start = NULL;
//	head->finish = NULL;
//	head->rooms = NULL;
//	return (head);
//}



t_lem		*lm_create_lem(void)
{
	t_lem	*head;

	if (!(head = (typeof(head))malloc(sizeof(*head))))
		return (NULL);
	*head = (typeof(*head)){ 0, 0, 0 ,0 ,0 ,0 ,0};
	head->gnl = (t_gnl_buff*)malloc(sizeof(t_gnl_buff));
	head->gnl->gnl = 0;
	head->gnl->next = NULL;
	head->ways = 0;
	return (head);
}
