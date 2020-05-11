/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/05/11 17:25:43 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**  creates a node for linked list which is a queue
*/
void			create_tqueue_node(t_obj *obj)
{
	// printf("inside %s\n", __func__);
	if (START_RM->level == 0)
	{
		START_RM->level = 1;
		START_RM->on_path = 1;
	}
	QCURRENT = ft_memalloc(sizeof(t_queue));
	QCURRENT->parent_room = ROOM;
	QCURRENT->current_room = ROOM->links->room;
	QCURRENT->current_room->queue = QCURRENT;
	ROOM->links->on_queue = 1;
	QCURRENT->current_room->level = ROOM->level + 1;
	// QCURRENT->next_queue = NULL;
	// QCURRENT->next_room = NULL;
	// QCURRENT->prev_queue = NULL;
	if (!QSTART)
		QSTART = QCURRENT;
	else
	{
		QEND->next_room = QCURRENT->current_room;
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
		
		if (ROOM->path && ROOM->path->next_room)
			printf("line %d next name:%p qend:%s\n", __LINE__, ROOM->path->next_room, QEND->current_room->name);
		if (ROOM->path && ROOM->path->next_room == END_RM)
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
**	from D(room) -> B(lnkd room)), and if it has, will not create the node 
*/
void			check_room_add_to_queue(t_obj *obj)
{
	printf("	check_room:%s check_room queue:%p\n", ROOM->links->room->name, ROOM->links->room->queue );
	if (ROOM->links->room->queue == 0)// || ROOM->links->room->queue->parent_room != ROOM)
	{
		printf("	2check_room room->links->room:%s path:%p\n", ROOM->links->room->name, ROOM->links->room->path);
		if (ROOM->path && ROOM->path->next_room == ROOM->links->room)
			return ;
		
		// this statement ensures that if a node has been on a path, it must
		// take one step backward on said path, so the only link that can be
		// added to the queue is the parent node of that node's path
		if (ROOM->path && QEND && ROOM->path->next_room != QEND->parent_room)
		{
			if (ROOM->links->room != ROOM->path->parent_room)
				return ;
		}
		if (ROOM->links->room->path)
		{
			if (ROOM->links->room->path->parent_room)
				printf("	chck room->links->path->parent:%s\n", ROOM->links->room->path->parent_room->name);
			if (ROOM->links->room->path->parent_room == ROOM)
				return ;
		}
		printf("	3 room %s added\n", ROOM->links->room->name);
		create_tqueue_node(obj);
	}
}
// void			check_room_add_to_queue(t_obj *obj)
// {
// 	printf("	check_room:%s check_room queue:%p\n", ROOM->links->room->name, ROOM->links->room->queue );
// 	if (ROOM->links->on_queue == 0)// || ROOM->links->room->queue->parent_room != ROOM)
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
	t_queue		*q_pointer;

	q_pointer = NULL;
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
		q_pointer = q_pointer ? q_pointer->next_queue : QSTART;
		ROOM = q_pointer ? q_pointer->current_room : NULL;
		if (ROOM)
			printf("3 BFS()room:%s parent:%s\n", ROOM->name, ROOM->queue->parent_room->name);
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




// deleted tqueue list but keep rooms that are on path

void			assign_path(t_obj *obj, t_room *room)
{	
	room->on_path = 1;
	if (room != START_RM)
		assign_path(obj, room->queue->parent_room);
}

void			delete_tqueue_nodes(t_obj *obj, t_room *room)
{
	printf("parent:%-7s name: %-7s on_path:%d\n", room->queue->parent_room->name, room->name, room->on_path);
	if (room->queue != QEND)
		delete_tqueue_nodes(obj, room->queue->next_room);
	if (room->on_path == 0)
	{
		room->on_queue = 0;
		printf("deleting node parent:%-7s name:  %-7s temp:%p\n", room->queue->parent_room->name, room->name, room->queue);
		ft_memdel((void*)&(room->queue));
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
// 			parent->queue->next_room = queue->current_room;
// 	}

// }

void			connect_tqueue_nodes(t_obj *obj, t_room *room, t_room *next_room)
{
	t_room		*temp;

	printf("%s room: %s\n", __func__, room->name);
	if (next_room)
		printf("next: %s\n", next_room->name);
	room->on_path = 0;
	temp = NULL;
	if (QSTART)
		QSTART = NULL;
	room->queue->next_room = next_room;

	if (!room->path)
		room->path = room->queue;
	else
	{
		if (room->path->parent_room == room->queue->next_room)
			room->path->parent_room = room->queue->parent_room;
		else if (room->path->next_room == room->queue->parent_room)
			room->path->next_room = room->queue->next_room;
	}

	temp = room->queue->parent_room;
	room->queue = NULL;
	if (temp != START_RM)
		connect_tqueue_nodes(obj, temp, room);
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
8_map.txt
		A	B	C
		D	E	F
Strt	G	H	I	end
		J	K	L
*/