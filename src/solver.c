/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 12:12:33 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/22 20:33:57 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**  creates a node for linked list which is a queue
*/
void			create_tqueue_node(t_obj *obj)
{
	if (START_RM->level == 0)
		START_RM->level = 1;
	CCURRENT->links->room->on_queue = 1;
	CCURRENT->on_queue = 1;
	QCURRENT = ft_memalloc(sizeof(t_queue));
	QCURRENT->parent_room = CCURRENT;
	QCURRENT->current_room = CCURRENT->links->room;
	QCURRENT->current_room->queue = QCURRENT;
	QCURRENT->current_room->level = CCURRENT->level + 1;
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
	t_queue		*temp;

	temp = NULL;
	CCURRENT = START_RM;
	while (CCURRENT && CCURRENT != END_RM)
	{
		if (CCURRENT->start_link)
			CCURRENT->links = CCURRENT->start_link;
		while (CCURRENT->links)
		{
			// if (!CCURRENT->links->room->queue || (CCURRENT->links->room->queue && CCURRENT->links->room->queue->parent_room != CCURRENT))
			if (CCURRENT->links->room->on_queue == 0)
				create_tqueue_node(obj);
			if (CCURRENT->links->room == END_RM)
				return ;
			CCURRENT->links = CCURRENT->links->next;
		}
		if (!temp)
			temp = QSTART;
		else
			temp = temp->next_queue;
		CCURRENT = temp ? temp->current_room : NULL;
	}
}


