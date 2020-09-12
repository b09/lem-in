/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/07/20 13:36:25 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

/*
**  creates a node for linked list which is a queue
*/

void			create_tqueue_node(t_lemin *lemin)
{
	lemin->temp_q = ft_memalloc(sizeof(t_queue));
	lemin->temp_q->prnt_rm = lemin->room;
	lemin->temp_q->parent_queue = lemin->curr_q;
	lemin->temp_q->parent_tlink_to_child = lemin->room->links;
	lemin->room->links->queue = lemin->temp_q;
	lemin->temp_q->room = lemin->room->links->room;
	lemin->temp_q->room->queue = lemin->temp_q;
	lemin->temp_q->level = assign_level(lemin);
	if (!lemin->head_q)
		lemin->head_q = lemin->temp_q;
	else
	{
		if (lemin->tail_q && lemin->temp_q->level < lemin->tail_q->level
			&& lemin->room->links->room != lemin->end_room)
		{
			lemin->temp_q->next = lemin->curr_q->next;
			lemin->curr_q->next = lemin->temp_q;
			lemin->temp_q->parent_queue = lemin->curr_q;
			lemin->tail_q = lemin->temp_q->next ? lemin->tail_q : lemin->temp_q;
			return ;
		}
		else
			lemin->tail_q->next = lemin->temp_q;
	}
	lemin->tail_q = lemin->temp_q;
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
**		lemin->start_room will not have a path, so if statement must be described
**		from perspective of child as well (see first if)
**	third if:
**		do not create a node for the parent of the current room, as it will have
**		been on the queue already.
**	fourth if:
**		if the current room, which has a path, has been added to the queue from
**		parent room which was not on a path, only allow the edge of the current
**		room which goes against the path.
*/

void			check_room_add_to_queue(t_lemin *lemin)
{
	if (lemin->room->links->room != lemin->start_room
		&& lemin->room->links->room->dead_end == 0)
	{
		if (lemin->room->links->queue != 0)
		{
			if (lemin->room->links->queue->level <= assign_level(lemin))
				return ;
		}
		if (lemin->room->path
			&& lemin->room->path->child_room == lemin->room->links->room)
			return ;
		if (lemin->room->links->room->path
			&& lemin->room->links->room->path->prnt_rm == lemin->room)
			return ;
		if (check_parent_queue(lemin))
			return ;
		if (lemin->room->path && lemin->curr_q)
		{
			if (!lemin->curr_q->prnt_rm->path
				&& lemin->room->links->room != lemin->room->path->prnt_rm)
				return ;
		}
		create_tqueue_node(lemin);
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

void			breadth_first_search(t_lemin *lemin, int paths)
{
	lemin->curr_q = NULL;
	lemin->room = lemin->start_room;
	while (lemin->room && lemin->room != lemin->end_room)
	{
		lemin->room->links = lemin->room->head_lnk;
		while (lemin->room->links)
		{
			check_room_add_to_queue(lemin);
			if (check_endrm(lemin))
				return ;
			lemin->room->links = lemin->room->links->next;
		}
		lemin->curr_q = lemin->curr_q ? lemin->curr_q->next : lemin->head_q;
		lemin->room = lemin->curr_q ? lemin->curr_q->room : NULL;
	}
	if (!paths && (!lemin->tail_q || lemin->tail_q->room != lemin->end_room))
		print_error(NO_PATH);
}

/*
**	queue nodes will assigned as path_nd in each room, if room does not already
**	have a path_nd. If it already has a path_nd, both path_nd and new queue will
**	be merged, resulting in new path/route.
**	the end_rm will only once have its queue become a path_nd once, as the rest
**	of the func() requires the current queue node to have a child_room, which
**	end_rm will not have.
*/

void			connect_tqueue_nodes(t_lemin *lemin)
{
	t_queue		*queue;

	queue = lemin->tail_q->parent_queue;
	queue->child_room = lemin->end_room;
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
	if (lemin->tail_q)
		ft_memdel((void*)&lemin->tail_q);
	lemin->head_q = NULL;
	lemin->tail_q = NULL;
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
