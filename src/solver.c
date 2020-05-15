/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/05/14 19:12:16 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**  creates a node for linked list which is a queue
*/
void			create_tqueue_node(t_obj *obj)
{
	printf("			inside %s creating tqueue" C_RED " %s " C_RESET "from parent %s\n", __func__, ROOM->links->room->name, ROOM->name);
	QHEAD && QHEAD->parent_room->path && printf(C_GREEN"		qhead parent:%s\n"C_RESET, QHEAD->parent_room->path->parent_room->name);
	// if (START_RM->level == 0)
	// {
	// 	START_RM->level = 1;
	// 	// START_RM->on_path = 1;
	// }
	QCURRENT = ft_memalloc(sizeof(t_queue));
	QCURRENT->parent_room = ROOM;
	QCURRENT->parent_queue = QHEAD;
	QCURRENT->parent_links_child = ROOM->links;
	QCURRENT->current_room = ROOM->links->room;
	QCURRENT->current_room->queue = QCURRENT;
	ROOM->links->on_queue_outgoing = 1;
	QCURRENT->level = QHEAD ? QHEAD->level + 1 : 1;

	if (!QSTART)
		QSTART = QCURRENT;
	else
	{

		QEND->next_queue = QCURRENT;
		QCURRENT->prev_queue = QEND;
	}
	QEND = QCURRENT;
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
		// printf("line %d\n", __LINE__);
	if (ROOM->links->room == END_RM)
	{
		// ROOM->path && ROOM->path->child_room && printf("line %d next name:%p qend:%s\n", __LINE__, ROOM->path->child_room, QEND->current_room->name);
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
void			check_room_add_to_queue(t_obj *obj)
{
	if (ROOM->links->on_queue_outgoing == 0 && ROOM->links->room != START_RM)
	{
		printf("%s() line:%d\n", __func__, __LINE__);
		ROOM->links->room->path && ROOM->links->room->path->parent_room && printf("		room-lnx->room: %s parent_path of aforementioned room %s\n", ROOM->links->room->name, ROOM->links->room->path->parent_room->name);

		if (ROOM->path && ROOM->path->child_room == ROOM->links->room)
		{
			// printf(C_YELLOW"	first return line %d\n"C_RESET, __LINE__);
			return ;
		}
		if (ROOM->links->room->path && ROOM->links->room->path->parent_room == ROOM)
		{
			// printf(C_MAGENTA"	second return line %d\n"C_RESET, __LINE__);
			return ;
		}

		if (QHEAD && QHEAD->parent_room && QHEAD->parent_room == ROOM->links->room)
		{
			// printf(C_RED"	fourth return line %d\n"C_RESET, __LINE__);
			// printf("	qhead current %s parent %s\n", QHEAD->current_room->name, QHEAD->parent_room->name);
			return ;
		}
		
		// if b, c, d, g, is a path && 
		// QHEAD->parent == 'a' (not part of path) && 
		// ROOM == 'c'
		// then QHEAD->parent_room->path == 0 is true for 'a'
		// therefore ROOM->links->room for 'c' must only be valid if it goes
		// against the edge is was a path on, which is 'b'
		if (ROOM->path && QHEAD && QHEAD->parent_room)
		{
			if (!QHEAD->parent_room->path && ROOM->links->room != ROOM->path->parent_room)
			{
				// printf(C_BLUE"	fifth return line %d\n"C_RESET, __LINE__);
				// printf("	qhead current %s parent %s\n", QHEAD->current_room->name, QHEAD->parent_room->name);
				return ;
			}
		}

		create_tqueue_node(obj);
	}
}


// void			check_room_add_to_queue(t_obj *obj)
// {
// 	printf("	check_room:%s check_room queue:%p\n", ROOM->links->room->name, ROOM->links->room->queue );
// 	if (ROOM->links->room->queue == 0)// || ROOM->links->room->queue->parent_room != ROOM)
// 	{
// 		printf("	2check_room room->links->room:%s path:%p\n", ROOM->links->room->name, ROOM->links->room->path);
// 		if (ROOM->path && ROOM->path->next_room == ROOM->links->room)
// 			return ;
		
// 		// this statement ensures that if a node has been on a path, it must
// 		// take one step backward on said path, so the only link that can be
// 		// added to the queue is the parent node of that node's path
// 		if (ROOM->path && QEND && ROOM->path->next_room != QEND->parent_room)
// 		{
// 			if (ROOM->links->room != ROOM->path->parent_room)
// 				return ;
// 		}
// 		if (ROOM->links->room->path)
// 		{
// 			if (ROOM->links->room->path->parent_room)
// 				printf("	chck room->links->path->parent:%s\n", ROOM->links->room->path->parent_room->name);
// 			if (ROOM->links->room->path->parent_room == ROOM)
// 				return ;
// 		}
// 		printf("	3 room %s added\n", ROOM->links->room->name);
// 		create_tqueue_node(obj);
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
void			breadth_first_search(t_obj *obj)
{

	QHEAD = NULL;
	ROOM = START_RM;
	while (ROOM && ROOM != END_RM)
	{
		ROOM->links = ROOM->start_link;
		printf("\n1 BFS()parnt room:%s\n", ROOM->name);
		while (ROOM->links)
		{
			printf("2 BFS()child room:%s\n", ROOM->links->room->name);
			check_room_add_to_queue(obj);
			if (check_endrm(obj))
				return ;
			ROOM->links = ROOM->links->next;
		}
		QHEAD = QHEAD ? QHEAD->next_queue : QSTART;
		ROOM = QHEAD ? QHEAD->current_room : NULL;
		// if (ROOM)
		// 	printf("3 BFS()room:%s parent:%s\n", ROOM->name, ROOM->queue->parent_room->name);
	}
	// if (QEND != END_RM) // do something here, first make sure qend should be endroom
	// 	printf("quend does not equal end room");
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


// main.c ---   assign_path(obj, QEND);
void			assign_path(t_obj *obj, t_queue *queue)
{	
	// printf("assign_path current room: %s\n", queue->current_room->name);
	queue->q_on_path = 1;
	if (queue && queue->parent_room != START_RM)
		assign_path(obj, queue->parent_queue);
}
// void			assign_path(t_obj *obj)//, t_room *room)
// {	

// 	t_queue *queue;
// 	t_room *room;

// 	queue = QEND;
// 	room = NULL;
// 	if (queue)
// 	{
// 		queue->current_room->on_path = 1;
// 		queue->current_room->queue = queue;
// 		room = queue->parent_room;
// 	}
// 	while (queue && queue->current_room != START_RM)
// 	{
// 			printf("queueroom: %s roomname:%s\n", queue->current_room->name, room->name);
// 			queue->parent_room && printf("parent room: %s\n", queue->parent_room->name);
// 		if (queue->current_room == room)
// 		{
// 			printf("change of room\n\n");
// 			queue->current_room->on_path = 1;
// 			queue->current_room->queue = queue;
// 			room = queue->parent_room;
// 			queue->current_room && room && printf("queue is %s now looking for %s\n\n", queue->current_room->name, room->name);
// 		}
// 		else
// 		{
// 			room->on_queue_outgoing = 0;
// 			ft_memdel((void*)&(room->queue));
// 		}

// 		queue = queue->prev_queue;
// 	}
// }

void			print_queue_from_qend(t_obj *obj)
{
	t_queue *queue;

	printf("%s()\n", __func__);
	queue = QEND;
	while (queue)
	{
		queue->current_room && printf("current room:%s ", queue->current_room->name);
		queue->parent_room && printf("parent: %s ", queue->parent_room->name);
		queue->child_room && printf("child: %s ", queue->child_room->name);
		printf("\n");
		queue = queue->prev_queue;
	}
}

void			delete_tqueue_nodes(t_obj *obj, t_queue *queue)
{
	printf("parent:%-7s name: %-7s on_path:%d\n", queue->parent_room->name, queue->current_room->name, queue->q_on_path);
	if (queue != QEND)
		delete_tqueue_nodes(obj, queue->next_queue);
	queue->parent_links_child->on_queue_outgoing = 0;
	if (queue->q_on_path == 0)
	{
		// room->on_queue_outgoing = 0;
		// printf("deleting node parent:%-7s name:  %-7s temp:%p\n", room->queue->parent_room->name, room->name, room->queue);
		ft_memdel((void*)&(queue));
		// printf("t_queue addr after delete: %p\n", (room->queue));

	}
}

/*
go through all queue nodes, don't delete for now, 
*/


// void			2connect_tqueue_nodes(t_obj *obj, t_queue *queue)
// {
// 	t_room		*parent;

// 	parent = NULL;
// 		parent = queue->parent_room;
// 	while (queue)
// 	{
// 		if (queue->current_room == parent)
// 			parent->queue->child_room = queue->current_room;
// 	}

// }

// void			connect_tqueue_nodes(t_obj *obj, t_room *room, t_room *child_room)
// {
// 	t_room		*temp;

// 	printf("%s room: %p\n", __func__, room);
// 	if (child_room)
// 		printf("next: %s\n", child_room->name);
// 	printf("Line: %d\n", __LINE__);
// 	if (room)
// 		room->on_path = 0;
// 	temp = NULL;
// 	if (QSTART)
// 		QSTART = NULL;
// 	room->queue->child_room = child_room;

// 	if (!room->path)
// 	{
// 		room->path = room->queue;
// 	}
// 	else
// 	{
// 		if (room->path->parent_room == room->queue->child_room)
// 			room->path->parent_room = room->queue->parent_room;
// 		else if (room->path->child_room == room->queue->parent_room)
// 			room->path->child_room = room->queue->child_room;
// 	}

// 	temp = room->queue->parent_room;
// 	printf("temp assignmnet %p\n", temp);
// 	room->queue = NULL;
// 	if (temp != START_RM)
// 	{

// 		connect_tqueue_nodes(obj, temp, room);
// 	}
// }

// main.c:		connect_tqueue_nodes(obj, (obj->q_end->current_room), 0);
void			connect_tqueue_nodes(t_obj *obj)//, t_room *room, t_room *child_room)
{
	t_queue *queue;

	queue = QEND;
	if (QSTART)
		QSTART = NULL;

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

