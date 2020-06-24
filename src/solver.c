/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/24 20:06:02 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**  creates a node for linked list which is a queue
*/
void			create_tqueue_node(t_obj *obj)//, bool negative_level)
{
	obj->tail_q = ft_memalloc(sizeof(t_queue));
	obj->tail_q->prnt_rm = obj->room;
	obj->tail_q->parent_queue = obj->curr_q;
	obj->room->links->queue = obj->tail_q;
	obj->tail_q->room = obj->room->links->room;
	obj->tail_q->room->queue = obj->tail_q;
	obj->tail_q->level = assign_level(obj);
	if (!obj->head_q)
		obj->head_q = obj->tail_q;
	else
	{
		if (obj->q_end && obj->tail_q->level < obj->q_end->level && obj->room->links->room != obj->end_room)// && !obj->curr_q->next)
		{
			obj->tail_q->next = obj->curr_q->next;
			obj->curr_q->next = obj->tail_q;
			obj->tail_q->parent_queue = obj->curr_q;
			if (!obj->tail_q->next)
				obj->q_end = obj->tail_q;
			return ;
		}	
		else
			obj->q_end->next = obj->tail_q;
	}
	obj->q_end = obj->tail_q;
}

int				assign_level(t_obj *obj)
{
	if (obj->curr_q)
	{
		if (obj->room->path && obj->room->path->prnt_rm == obj->room->links->room)
			return (obj->curr_q->level - 1);
		else
			return (obj->curr_q->level + 1);
	}
	return (1);

}

/*
**	called in bfs() while loop
**	will exit bfs() if func() returns 1
**	Returns 1 if the current room links to end room (therefore end found)
**	but not if link between current room and end room has been used before in 
**	previous bfs() call which resulted in a valid path. 
*/
int				check_endrm(t_obj *obj)
{
	if (obj->room->links->room == obj->end_room)
	{
		if (obj->room->path && obj->room->path->child_room == obj->end_room)
		{
			return (0);
		}
		return (1);
	}
	return (0);
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
		// obj->room->links->room->path && obj->room->links->room->path->prnt_rm && printf("		room-lnx->room: %s parent_path of aforementioned room %s\n", obj->room->links->room->name, obj->room->links->room->path->prnt_rm->name);
			// printf(C_MAGENTA"	second return line %d\n"C_RESET, __LINE__);
			// printf(C_RED"	fourth return line %d\n"C_RESET, __LINE__);
			// printf("	qhead current %s parent %s\n", obj->curr_q->room->name, obj->curr_q->prnt_rm->name);
				// printf(C_BLUE"	fifth return line %d\n"C_RESET, __LINE__);
				// printf("	qhead current %s parent %s\n", obj->curr_q->room->name, obj->curr_q->prnt_rm->name);
	// print_queue_from_qend(obj);
*/
void			check_room_add_to_queue(t_obj *obj)
{
	if (obj->room->links->room != obj->start_room && obj->room->links->room->dead_end == 0)
	{
		if (obj->room->links->queue != 0)
		{
			if (obj->room->links->queue->level <= assign_level(obj))
				return ;
		}
		if (obj->room->path && obj->room->path->child_room == obj->room->links->room)
			return ;
		if (obj->room->links->room->path && obj->room->links->room->path->prnt_rm == obj->room)
			return ;
		if (check_parent_queue(obj))
			return ;
		if (obj->room->path && obj->curr_q)// && obj->curr_q->prnt_rm)
		{
			if (!obj->curr_q->prnt_rm->path && obj->room->links->room != obj->room->path->prnt_rm)
				return ;
		}
		create_tqueue_node(obj);//, 0);
	}
}

int				check_parent_queue(t_obj *obj)
{
	t_link		*links;
	
	links = obj->room->links->room->head_lnk;
	while (links)
	{
		if (links->room == obj->room && links->queue)
		{
			return (1);
		}
		links = links->next;
	}
	return (0);

}

/*
**	func() will create a queue of rooms
**	each room will only be added to the queue once
**	All rooms(level 1) that link to the start room will be added to the queue, 
**	as well as all rooms(level 2) that link to the first rooms(level 1) and so
**	on until the end room is found. If func() is called more than once, a room
**	will not be added to the queue if that room is on path WITH THE SAME EDGE
**	 
*/

void			breadth_first_search(t_obj *obj)
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
}

void			assign_path(t_obj *obj, t_queue *queue)
{	
	queue->assign_to_path = 1;
	if (queue && queue->prnt_rm != obj->start_room)
		assign_path(obj, queue->parent_queue);
}

void			print_queue_from_qend(t_obj *obj)
{
	t_queue		*queue;

	printf("%s()\n", __func__);
	queue = obj->head_q;
	while (queue)
	{
		queue->room && printf("level: %d current room:%s ", queue->level, queue->room->name);
		queue->prnt_rm && printf("parent: %s ", queue->prnt_rm->name);
		queue->child_room && printf("child: %s ", queue->child_room->name);
		printf("\n");
		if (queue == obj->curr_q)
			printf(C_BLUE"	^^^^^ QHEAD ^^^^\n"C_RESET);
		queue = queue->next;
	}
	printf("\n");
}

void			delete_tqueue_nodes(t_obj *obj, t_queue *queue)
{
	if (queue != obj->q_end)
		delete_tqueue_nodes(obj, queue->next);
	if (queue->assign_to_path == 0)
		ft_memdel((void*)&(queue));
}

void			connect_tqueue_nodes(t_obj *obj)
{
	t_queue		*queue;

	queue = obj->q_end;
	obj->head_q = NULL;
	obj->q_end = NULL;
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
