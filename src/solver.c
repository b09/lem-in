/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/30 20:06:05 by macbook       ########   odam.nl         */
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
	QCURRENT->current_room->level = ROOM->level + 1;
	QCURRENT->next_queue = NULL;
	QCURRENT->next_room = NULL;
	if (!QSTART)
		QSTART = QCURRENT;
	else
	{
		QEND->next_room = QCURRENT->current_room;
		QEND->next_queue = QCURRENT;
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
	if (ROOM->links->room == END_RM)
	{
		if (ROOM->path && ROOM->path->next_room == END_RM)
			return (0);
		return (1);
	}
	return (0);
}

/*
**	called in bfs() while loop
**	func() will create t_queue node and add to the t_queue lnkd list if
**	current link of room is not already on linked list.
**	If linked room is on valid path from a previous bfs() call, func() will 
**	check that edge has been used before (A(room) -> B(lnkd room) differs 
**	from D(room) -> B(lnkd room)), and if it has, will not create the node 
*/
void			check_room_add_to_queue(t_obj *obj)
{
	if (ROOM->links->room->queue == 0)
	{
		if (ROOM->links->room->path)
		{
			if (ROOM->links->room->path->parent_room == ROOM)
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
**	on until the end room is found.
**	 
*/
void			breathe_first_search(t_obj *obj)
{
	t_queue		*q_pointer;

	q_pointer = NULL;
	ROOM = START_RM;
	// start looking at links in startroom
	while (ROOM && ROOM != END_RM)
	{
		ROOM->links = ROOM->start_link;
		// while those rooms are not on the queue, add them to the queue
		while (ROOM->links)
		{
			check_room_add_to_queue(obj);
			if (check_endrm(obj))
				return ;
			ROOM->links = ROOM->links->next;
		}
		q_pointer = q_pointer ? q_pointer->next_queue : QSTART;
		ROOM = q_pointer ? q_pointer->current_room : NULL;
	}
}








// deleted tqueue list but keep rooms that are on path

void			assign_path(t_obj *obj, t_room *room)
{	
	room->on_path = 1;
	if (room != START_RM)
		assign_path(obj, room->queue->parent_room);
}

void			delete_tqueue_nodes(t_obj *obj, t_room *room)
{
	printf("parent:%-7s name: %-7s on_queue:%d\n", room->queue->parent_room->name, room->name, room->on_path);
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

void			connect_tqueue_nodes(t_obj *obj, t_room *room, t_room *next_room)
{
	t_room		*temp;

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


// void			connect_tqueue_nodes(t_obj *obj, t_room *room, t_room *next_room)
// {
// 	printf("inside %s room:%s\n", __func__, room->name);
// 	if (room != START_RM)
// 	{
// 		if (QSTART)
// 			QSTART = NULL;
// 		room->queue->next_room = next_room;
// 		// room->path = room->queue;


// 		if (!room->path)
// 			room->path = room->queue;
// 		else
// 		{
// 			if (room != END_RM)
// 			{
// 				printf("room:%s parent: %s child: %s\n", room->name, room->path->parent_room->name, room->path->next_room->name);
// 				printf("qroom:%s qparent: %s qchild: %s\n", room->name, room->queue->parent_room->name, room->queue->next_room->name);
// 			}
// 			else
// 			{
// 				printf("room:%s parent: %s child: %p\n", room->name, room->path->parent_room->name, room->path->next_room);
// 				printf("qroom:%s qparent: %s qchild: %p\n", room->name, room->queue->parent_room->name, room->queue->next_room);
// 			}
			
// 			// printf("queue:%s q parent: %s\n", room->name, room->queue->parent_room->name);
// 			if (room->path->parent_room == room->queue->next_room)
// 				room->path->parent_room = room->queue->parent_room;
// 			else if (room->path->next_room == room->queue->parent_room)
// 				room->path->next_room = room->queue->next_room;
// 			if (room != END_RM)
// 			{
// 				printf("2room:%s parent: %s child: %s\n", room->name, room->path->parent_room->name, room->path->next_room->name);
// 				printf("2qroom:%s qparent: %s qchild: %s\n\n", room->name, room->queue->parent_room->name, room->queue->next_room->name);
// 			}
// 			else
// 			{
// 				printf("2room:%s parent: %s child: %p\n", room->name, room->path->parent_room->name, room->path->next_room);
// 				printf("2qroom:%s qparent: %s qchild: %p\n\n", room->name, room->queue->parent_room->name, room->queue->next_room);
// 			}
// 		}
// 		// if (room != END_RM)
// 		// {
// 		// 	room->queue = NULL;
// 		// 	connect_tqueue_nodes(obj, room->path->parent_room, room);
// 		// }
// 		// else
// 		// {
// 		// 	t_room *temp = room->queue->parent_room;
// 		// 	room->queue = NULL;
// 		// 	connect_tqueue_nodes(obj, temp, room);
// 		// }
// 			t_room *temp = room->queue->parent_room;
// 			room->queue = NULL;
// 			connect_tqueue_nodes(obj, temp, room);




// 		// connect_tqueue_nodes(obj, room->path->parent_room, room);
// 	}
// }

