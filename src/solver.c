/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/27 20:34:27 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**  creates a node for linked list which is a queue
*/
void			create_tqueue_node(t_obj *obj)
{
	printf("inside %s\n", __func__);
	if (START_RM->level == 0)
	{
		START_RM->level = 1;
		START_RM->on_path = 1;
	}
	ROOM->links->room->on_queue = 1;
	ROOM->on_queue = 1;
	QCURRENT = ft_memalloc(sizeof(t_queue));
	QCURRENT->parent_room = ROOM;
	QCURRENT->current_room = ROOM->links->room;
	QCURRENT->current_room->queue = QCURRENT;
	QCURRENT->current_room->level = ROOM->level + 1;
	QCURRENT->next_queue = NULL;
	if (!QSTART)
	{
		QSTART = QCURRENT;
	}
	else
		QEND->next_queue = QCURRENT;
	QEND = QCURRENT;
}

/*
**
*/
void			create_tqueue_lst(t_obj *obj)
{
	t_queue		*q_pointer;

	q_pointer = NULL;
	ROOM = START_RM;
	while (ROOM && ROOM != END_RM)
	{
		if (ROOM->start_link)
			ROOM->links = ROOM->start_link;
		while (ROOM->links)
		{
			if (ROOM->links->room->on_queue == 0)
			{
				create_tqueue_node(obj);
			}
			if (ROOM->links->room == END_RM)
				return ;
			ROOM->links = ROOM->links->next;
		}
		if (!q_pointer)
			q_pointer = QSTART;
		else
			q_pointer = q_pointer->next_queue;
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

void			delete_tqueue_nodes(t_obj *obj, t_queue **temp)
{
	printf("name: %-7s parent:%-7s on_queue:%d\n", (*temp)->current_room->name, (*temp)->parent_room->name, (*temp)->current_room->on_path);
	if (*temp != QEND)
		delete_tqueue_nodes(obj, &(*temp)->next_queue);
	if ((*temp)->current_room->on_path == 0)
	{
		(*temp)->current_room->on_queue = 0;
		printf("deleting node: %-7s parent:%-7s temp:%p\n", (*temp)->current_room->name, (*temp)->parent_room->name, *temp);
		ft_memdel((void*)&(*temp));
	}
}

void			connect_tqueue_nodes(t_obj *obj, t_queue *node)
{
	if (node->parent_room != START_RM)
	{
		node->parent_room->queue->next_queue = node;
		connect_tqueue_nodes(obj, node->parent_room->queue);
	}
	else
		QSTART = node;
}

