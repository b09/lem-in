/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 17:41:22 by macbook       #+#    #+#                 */
/*   Updated: 2020/07/20 13:37:57 by bprado        ########   odam.nl         */
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
	if ((*list)->head_lnk)
		delete_tlink_lst(&(*list)->head_lnk);
	if ((*list)->path)
		ft_memdel((void*)&(*list)->path);
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_troom_lst(&(*list)->next);
		ft_memdel((void*)&(*list)->name);
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
	if (obj->head_tstr)
		delete_string_lst(&obj->head_tstr);
	if (obj->head_rm)
		delete_troom_lst(&obj->head_rm);
	if (obj->head_q)
		delete_tqueue_nodes(obj, obj->head_q, 1);
}

/*
**	parentroom && childroom are vertices
**	parentroom->links->childroom is an edge
**	queue->parent_tlink_to_child->queue = 0 is an interesting line ...
**	parent_tlink_to_child is the only access that each t_queue node
**	has to the parent->links->queue member, which is itself used to
**	evaluate in check_room_add_to_queue() whether the current
**	parentroom->links->childroom edge is valid, and can be added to the queue.
**	each links node in parentroom describes the edges that parentroom has
**	to each of its children, and when a childroom is added to a queue, the
**	parentroom's link node will have the childroom's t_queue pointer added
**	to it as it's queue member. In other words, when parentroom wants to add
**	childroom to the queue, if childroom is already on the queue, parentroom
**	will have a pointer to that exact t_queue node in the linked list of
**	queue nodes where the edge parentroom->links->childroom is contained.
**	as delete_tqueue_nodes() deletes from childroom to parentroom, the func()
**	needs access to parentroom's link to childroom, and it needs to access
**	it from childroom, so that, if the bfs() runs again, it will add the edge
**	of parentroom->links->childroom to the queue if that edge was not used on
**	a previous bfs() call which resulted with that edge being on a path.
**	otherwise, if parentroom->links->childroom was ever added to the queue,
**	that edge will never be added to the queue again, even if that edge could
**	lead to a valid path on later bfs() calls.
*/

void			delete_tqueue_nodes(t_obj *obj, t_queue *queue, char del_all)
{
	if (queue && queue != obj->tail_q)
		delete_tqueue_nodes(obj, queue->next, del_all);
	if (del_all == 0 && queue)
	{
		queue->parent_tlink_to_child->queue = 0;
		if (queue->assign_to_path == 0)
		{
			ft_memdel((void*)&(queue));
			queue = NULL;
		}
	}
	else
	{
		ft_memdel((void*)&(queue));
		if (queue == obj->head_q)
			queue = NULL;
	}
}
