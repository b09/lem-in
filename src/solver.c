/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/21 19:39:37 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**  creates a node for linked list which is a queue
*/
void			create_tqueue_node(t_obj *obj)//, bool negative_level)
{
	// printf("			inside %s creating tqueue" C_RED " %s " C_RESET "from parent %s\n", __func__, ROOM->links->room->name, ROOM->name);
	// QHEAD && QHEAD->parent_room->path && printf(C_GREEN"			QHEAD->parent_room->path->parent_room->name:%s\n"C_RESET, QHEAD->parent_room->path->parent_room->name);
			// QHEAD && QHEAD->parent_room && printf("		qhead:%s qheadparent:%s\n", QHEAD->current_room->name, QHEAD->parent_room->name);

	QCURRENT = ft_memalloc(sizeof(t_queue));
	QCURRENT->parent_room = ROOM;
	QCURRENT->parent_queue = QHEAD;
	QCURRENT->parent_links_child = ROOM->links;
	ROOM->links->lnk_queue = QCURRENT;
	QCURRENT->current_room = ROOM->links->room;
	QCURRENT->current_room->queue = QCURRENT;
	ROOM->links->on_queue_outgoing = 1;
	QCURRENT->level = assign_level(obj);
	// printf("		level for new qcurrent: %d\n", QCURRENT->level);
	if (!QSTART)
		QSTART = QCURRENT;
	else
	{
		if (QEND && QCURRENT->level < QEND->level && ROOM->links->room != END_RM)// && !QHEAD->next_queue)
		{
		// printf(C_RED"%s() %d node:%s\n"C_RESET, __func__, __LINE__, QCURRENT->current_room->name);
			QCURRENT->next_queue = QHEAD->next_queue;
			QHEAD->next_queue = QCURRENT;
			QCURRENT->parent_queue = QHEAD;
			// QCURRENT->next_queue && printf("%s() qcurrent:%s qcurrent->next:%s\n", __func__, QCURRENT->current_room->name, QCURRENT->next_queue->current_room->name);
			if (!QCURRENT->next_queue)
				QEND = QCURRENT;
			return ;
		}	
		else
		{
		// printf(C_CYAN"%s() %d node:%s\n"C_RESET, __func__, __LINE__, QCURRENT->current_room->name);
			QEND->next_queue = QCURRENT;
			QCURRENT->prev_queue = QEND;
		}
	}
	QEND = QCURRENT;
}

int				assign_level(t_obj *obj)
{
	if (QHEAD)
	{
		if (ROOM->path && ROOM->path->parent_room == ROOM->links->room)
			return (QHEAD->level - 1);
		else
			return (QHEAD->level + 1);
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
	// printf("line %d\n", __LINE__);
	// ROOM->path && ROOM->path->child_room && printf("line %d next name:%p qend:%s\n", __LINE__, ROOM->path->child_room, QEND->current_room->name);
int				check_endrm(t_obj *obj)
{
	if (ROOM->links->room == END_RM)
	{
		if (ROOM->path && ROOM->path->child_room == END_RM)
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
**		start_rm will not have a path, so if statement must be described
**		from perspective of child as well (see first if)
**	third if:
**		do not create a node for the parent of the current room, as it will have
**		been on the queue already.
**	fourth if:
**		if the current room, which has a path, has been added to the queue from 
**		parent room which was not on a path, only allow the edge of the current
**		room which goes against the path.
*/
		// ROOM->links->room->path && ROOM->links->room->path->parent_room && printf("		room-lnx->room: %s parent_path of aforementioned room %s\n", ROOM->links->room->name, ROOM->links->room->path->parent_room->name);
			// printf(C_MAGENTA"	second return line %d\n"C_RESET, __LINE__);
			// printf(C_RED"	fourth return line %d\n"C_RESET, __LINE__);
			// printf("	qhead current %s parent %s\n", QHEAD->current_room->name, QHEAD->parent_room->name);
				// printf(C_BLUE"	fifth return line %d\n"C_RESET, __LINE__);
				// printf("	qhead current %s parent %s\n", QHEAD->current_room->name, QHEAD->parent_room->name);
void			check_room_add_to_queue(t_obj *obj)
{
		// printf("%s() line:%d ROOM->links->room:%s\n", __func__, __LINE__, ROOM->links->room->name);
	// print_queue_from_qend(obj);
	if (ROOM->links->room != START_RM && ROOM->links->room->dead_end == 0)
	{
		if (ROOM->links->lnk_queue != 0)
		{
			if (ROOM->links->lnk_queue->level <= assign_level(obj))
			{
			// printf("room %s room_link %s levl:%d assign_level%d\n", ROOM->name, ROOM->links->room->name, ROOM->links->lnk_queue->level, assign_level(obj));
			// QHEAD && QHEAD->parent_room && printf("		qhead:%s qheadparent:%s\n", QHEAD->current_room->name, QHEAD->parent_room->name);
			// printf(C_YELLOW"	first return line %d\n"C_RESET, __LINE__);
				return ;
			}
		}
		if (ROOM->path && ROOM->path->child_room == ROOM->links->room)
		{
			return ;
		}
		if (ROOM->links->room->path && ROOM->links->room->path->parent_room == ROOM)
		{
			return ;
		}
		// if (QHEAD && QHEAD->parent_room == ROOM->links->room)
		if (check_parent_queue(obj))
		{
			return ;
		}
		if (ROOM->path && QHEAD)// && QHEAD->parent_room)
		{
			if (!QHEAD->parent_room->path && ROOM->links->room != ROOM->path->parent_room)
			{
				return ;
			}
		}
		create_tqueue_node(obj);//, 0);
	}
	// if (ROOM->links->lnk_queue != 0)
	// 	check_parent_queue(obj);
}

int				check_parent_queue(t_obj *obj)
{
	// if (QHEAD && QHEAD->parent_room == ROOM->links->room)
	// 	{
	// 		return ;
	// 	}
	t_link		*links;
	links = ROOM->links->room->start_link;
	while (links)
	{
		if (links->room == ROOM && links->lnk_queue)
		{
			return (1);
		}
		links = links->next;
	}
	return (0);

}


// void			check_parent_queue(t_obj *obj)
// {
// 	// printf(C_YELLOW"1somethin goin on in %s\n"C_RESET, __func__);
// 	if (QHEAD)
// 	{
// 		if (ROOM->links->lnk_queue->level >= QHEAD->level)
// 		{
// 			// printf(C_YELLOW"2somethin goin on in %s\n"C_RESET, __func__);
// 			if (ROOM->path && ROOM->path->parent_room == ROOM->links->room)
// 			{
// 				// printf(C_YELLOW"3somethin goin on in %s\n"C_RESET, __func__);
// 				ROOM->links->lnk_queue->parent_queue = QHEAD;
// 			}
// 		}
// 	}

// }

/*
**	func() will create a queue of rooms
**	each room will only be added to the queue once
**	All rooms(level 1) that link to the start room will be added to the queue, 
**	as well as all rooms(level 2) that link to the first rooms(level 1) and so
**	on until the end room is found. If func() is called more than once, a room
**	will not be added to the queue if that room is on path WITH THE SAME EDGE
**	 
*/
		// 	printf("3 BFS()room:%s parent:%s\n", ROOM->name, ROOM->queue->parent_room->name);
		// print_queue_from_qend(obj);
		// QHEAD && printf("QHEAD:%s\n", QHEAD->current_room->name);
		// // QHEAD && QHEAD->next_queue && printf("QHEAD->next_queue:%s\n", QHEAD->next_queue->current_room->name);
		// QEND && printf("QEND:%s\n", QEND->current_room->name);
		// QEND && QEND->prev_queue && printf(" prev QEND:%s\n", QEND->prev_queue->current_room->name);
		// printf("QHEAD:%p\n", QHEAD);
		// QHEAD && printf("QHEAD:%s\n", QHEAD->current_room->name);
			// printf("2 BFS()child room:%s\n", ROOM->links->room->name);
		// printf("change of head\n\n\n");
void			breadth_first_search(t_obj *obj)
{

	QHEAD = NULL;
	ROOM = START_RM;
	while (ROOM && ROOM != END_RM)
	{
		ROOM->links = ROOM->start_link;

		// printf("\n1 BFS()ROOM->name:%s\n", ROOM->name);
		while (ROOM->links)
		{
			check_room_add_to_queue(obj);
			if (check_endrm(obj))
			{
				// print_queue_from_qend(obj);
				// QEND ? printf(C_RED"after bfs QEND:%d\n"C_RESET, QEND->level): printf(C_RED"no qend after bfs()\n"C_RESET);
				// print_multiple_paths(obj);
				return ;
			}
			ROOM->links = ROOM->links->next;
		}
		QHEAD = QHEAD ? QHEAD->next_queue : QSTART;
		ROOM = QHEAD ? QHEAD->current_room : NULL;
	}
	// if (QEND != END_RM) // do something here, first make sure qend should be endroom
	// 	printf("quend does not equal end room");
}




// main.c ---   assign_path(obj, QEND);
void			assign_path(t_obj *obj, t_queue *queue)
{	
	// printf("assign_path current room: %s\n", queue->current_room->name);
	queue->q_on_path = 1;
	if (queue && queue->parent_room != START_RM)
		assign_path(obj, queue->parent_queue);
}


void			print_queue_from_qend(t_obj *obj)
{
	// altered print_queue_from_qend to print from qstart instead of qend
	t_queue *queue;

	printf("%s()\n", __func__);
	queue = QSTART;
	while (queue)
	{
		queue->current_room && printf("level: %d current room:%s ", queue->level, queue->current_room->name);
		queue->parent_room && printf("parent: %s ", queue->parent_room->name);
		queue->child_room && printf("child: %s ", queue->child_room->name);
		printf("\n");
		if (queue == QHEAD)
			printf(C_BLUE"	^^^^^ QHEAD ^^^^\n"C_RESET);
		queue = queue->next_queue;
	}
	printf("\n");
}

void			delete_tqueue_nodes(t_obj *obj, t_queue *queue)
{
	// printf("parent:%-7s name: %-7s on_path:%d\n", queue->parent_room->name, queue->current_room->name, queue->q_on_path);
	if (queue != QEND)
		delete_tqueue_nodes(obj, queue->next_queue);
	queue->parent_links_child->on_queue_outgoing = 0;
	queue->parent_links_child->lnk_queue = 0;
	if (queue->q_on_path == 0)
	{
		// room->on_queue_outgoing = 0;
		// printf("deleting node parent:%-7s name:  %-7s temp:%p\n", room->queue->parent_room->name, room->name, room->queue);
		ft_memdel((void*)&(queue));
		// printf("t_queue addr after delete: %p\n", (room->queue));

	}
}




// main.c:		connect_tqueue_nodes(obj, (obj->q_end->current_room), 0);
void			connect_tqueue_nodes(t_obj *obj)//, t_room *room, t_room *child_room)
{
	t_queue *queue;

	queue = QEND;
	// if (QSTART)
		QSTART = NULL;
		QEND = NULL;

	while (queue)
	{
		if (queue->parent_queue)
		{
			queue->parent_queue->child_queue = queue;
			queue->parent_queue->child_room = queue->current_room;

		}
		if (!queue->current_room->path)
			queue->current_room->path = queue;
		else
		{
			if (queue->current_room->path->parent_room == queue->child_room)
				queue->current_room->path->parent_room = queue->parent_room;
			else if (queue->current_room->path->child_room == queue->parent_room)
				queue->current_room->path->child_room = queue->child_room;
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


// void			func_bfs(t_obj *obj)
// {
// 	int			i;

// 	i = count_links(START_RM);
// 	i = i < count_links(END_RM) ? i : count_links(END_RM);
// 	i = i < ANTS ? i : ANTS;

// }

/*
void			check_room_add_to_queue(t_obj *obj)
{
	if (ROOM->links->room != START_RM)
	{
		if (ROOM->links->lnk_queue)
			if (ROOM->links->lnk_queue->level + 1 < QCURRENT->level)
				return;
		if (ROOM->path && ROOM->path->child_room == ROOM->links->room)
		{
			return ;
		}
	}
}
*/