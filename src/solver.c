/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/28 18:32:07 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

/*
**  creates a node for linked list which is a queue
*/

void			create_tqueue_node(t_obj *obj)
{
	obj->temp_q = ft_memalloc(sizeof(t_queue));
	obj->temp_q->prnt_rm = obj->room;
	obj->temp_q->parent_queue = obj->curr_q;
	obj->room->links->queue = obj->temp_q;
	obj->temp_q->room = obj->room->links->room;
	obj->temp_q->room->queue = obj->temp_q;
	obj->temp_q->level = assign_level(obj);
	if (!obj->head_q)
		obj->head_q = obj->temp_q;
	else
	{
		if (obj->tail_q && obj->temp_q->level < obj->tail_q->level &&\
		obj->room->links->room != obj->end_room)
		{
			obj->temp_q->next = obj->curr_q->next;
			obj->curr_q->next = obj->temp_q;
			obj->temp_q->parent_queue = obj->curr_q;
			if (!obj->temp_q->next)
				obj->tail_q = obj->temp_q;
			return ;
		}
		else
			obj->tail_q->next = obj->temp_q;
	}
	obj->tail_q = obj->temp_q;
}

/*
**	called in bfs() while loop
**	func() will create t_queue node and add to the t_queue lnkd list if
**	current link of room is not already on linked list.
**	If linked room is on valid path from a previous bfs() call, func() will
**	check if that edge has been used before (A(room) -> B(lnkd room) differs
**	from D(room) -> B(lnkd room)), and if it has, will not create qnode
**
**	first if:
**		if child in path is the same as potential queue child, return.
**	second if:
**		obj->start_room will not have a path, so if statement must be described
**		from perspective of child as well (see first if)
**	third if:
**		do not create a node for the parent of the current room, as it will have
**		been on the queue already.
**	fourth if:
**		if the current room, which has a path, has been added to the queue from
**		parent room which was not on a path, only allow the edge of the current
**		room which goes against the path.
*/

void			check_room_add_to_queue(t_obj *obj)
{
	if (obj->room->links->room != obj->start_room &&\
	obj->room->links->room->dead_end == 0)
	{
		if (obj->room->links->queue != 0)
		{
			if (obj->room->links->queue->level <= assign_level(obj))
				return ;
		}
		if (obj->room->path && obj->room->path->child_room ==\
		obj->room->links->room)
			return ;
		if (obj->room->links->room->path &&\
		obj->room->links->room->path->prnt_rm == obj->room)
			return ;
		if (check_parent_queue(obj))
			return ;
		if (obj->room->path && obj->curr_q)
		{
			if (!obj->curr_q->prnt_rm->path && obj->room->links->room !=\
			obj->room->path->prnt_rm)
				return ;
		}
		create_tqueue_node(obj);
	}
}

/*
**	func() will create a queue of rooms
**	each room will only be added to the queue once
**	All rooms(level 1) that link to the start room will be added to the queue,
**	as well as all rooms(level 2) that link to the first rooms(level 1) and so
**	on until the end room is found. If func() is called more than once, a room
**	will not be added to the queue if that room is on path WITH THE SAME EDGE
*/

void			breadth_first_search(t_obj *obj, int paths)
{
	obj->curr_q = NULL;
	obj->room = obj->start_room;
	while (obj->room && obj->room != obj->end_room)
	{
		obj->room->links = obj->room->head_lnk;
		while (obj->room->links)
		{
			check_room_add_to_queue(obj);
			if (check_endrm(obj))
				return ;
			obj->room->links = obj->room->links->next;
		}
		obj->curr_q = obj->curr_q ? obj->curr_q->next : obj->head_q;
		obj->room = obj->curr_q ? obj->curr_q->room : NULL;
	}
	if (!paths && (!obj->tail_q || obj->tail_q->room != obj->end_room))
		print_error(NO_PATH);
}

void			connect_tqueue_nodes(t_obj *obj)
{
	t_queue		*queue;

	queue = obj->tail_q;
	obj->head_q = NULL;
	obj->tail_q = NULL;
	while (queue)
	{
		if (queue->parent_queue)
			queue->parent_queue->child_room = queue->room;
		if (!queue->room->path)
			queue->room->path = queue;
		else
		{
			if (queue->room->path->prnt_rm == queue->child_room)
				queue->room->path->prnt_rm = queue->prnt_rm;
			else if (queue->room->path->child_room == queue->prnt_rm)
				queue->room->path->child_room = queue->child_room;
		}
		queue = queue->parent_queue;
	}
}

int				count_links(t_link *links)
{
	int			i;

	i = 0;
	while (links)
	{
		links = links->next;
		++i;
	}
	return (i);
}

/*
**	loop over bfs() number of times that there are links in start or end,
**	or number of ants, whichever is smallest.
**	calculate smallest number of steps given for each bfs(), save number of
**	times bfs() needed to be called to have the smallest number of steps.
**	continues calling bfs() until number of links from start or end or number
**	of ants (whichever is smallest) is exhausted
*/
