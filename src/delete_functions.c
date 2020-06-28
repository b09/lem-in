/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 17:41:22 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/28 15:13:05 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void			delete_string_lst(t_str **list)
{
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_string_lst(&(*list)->next);
		ft_memdel((void*)&(*list)->str);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}

void			delete_troom_lst(t_room **list)
{
	if ((*list)->links)
		delete_tlink_lst(&(*list)->links);
	if ((*list)->path)
		ft_memdel((void*)&(*list)->path);
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_troom_lst(&(*list)->next);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}

void			delete_tlink_lst(t_link **list)
{
	if (*list)
	{
		if ((*list)->next)
			delete_tlink_lst(&(*list)->next);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}

void			delete_all(t_obj *obj)
{
	if (obj->tstr)
		delete_string_lst(&obj->tstr);
	if (obj->head_rm)
		delete_troom_lst(&obj->head_rm);
	exit(1);
}

void			delete_tqueue_nodes(t_obj *obj, t_queue *queue)
{
	if (queue != obj->tail_q)
		delete_tqueue_nodes(obj, queue->next);
	if (queue->assign_to_path == 0)
		ft_memdel((void*)&(queue));
}
