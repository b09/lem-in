/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/27 20:34:27 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

// using printf to print to screen
void			print_tstr_lst(t_obj *obj)
{
	TSTR_L = TSTR_STRT;
	printf("%s()\n", __func__);
	if (TSTR_L != NULL)
	{
		while (TSTR_L->next != NULL)
		{
			printf("addr:%p beginning:%p string:%s", TSTR_L, TSTR_STRT, (TSTR_L->str));
			TSTR_L = TSTR_L->next;
		}
			printf("addr:%p beginning:%p string:%s\n\n", TSTR_L, TSTR_STRT, (TSTR_L->str));
		TSTR_L = TSTR_STRT;
	}
}

void			print_troom_lst(t_obj *obj)
{
	ROOM = CSTART;
	printf("%s()\n", __func__);
	while (ROOM)
	{
		// printf("ROOM:%p, name:%s, coord_x:%d, coord_y:%d\nstart_rm:%p end_rm:%p\n", ROOM, ROOM->name, ROOM->coord_x, ROOM->coord_y, START_RM, END_RM);
		printf("ROOM:%p, name:%s, coord_x:%d, coord_y:%d\n", ROOM, ROOM->name, ROOM->coord_x, ROOM->coord_y);
		ROOM = ROOM->next;
	}
	printf("\n");
}

void			print_tlink_lst(t_obj *obj)
{
	printf("%s()\n", __func__);
	ROOM = CSTART;
	while (ROOM)
	{
		if (ROOM->start_link)
		{
			ROOM->links = ROOM->start_link;
			while (ROOM->links->next != NULL)
			{
				printf("Room: %s links to: %s\n", ROOM->name, ROOM->links->room->name);
				ROOM->links = ROOM->links->next;
			}
			printf("Room: %s links to: %s\n\n", ROOM->name, ROOM->links->room->name);
		}
		ROOM = ROOM->next;
	}
	// printf("exiting %s\n", __func__);
}


void			print_tqueue_lst(t_obj *obj)
{
	int 		i;
	i = 0;
	printf("%s()\n", __func__);
	QCURRENT = QSTART;
	while (QCURRENT != QEND)
	{
		printf("Room: %s links to room: %s		q addr: %p  level:%d\n", QCURRENT->parent_room->name, QCURRENT->current_room->name, QCURRENT, QCURRENT->current_room->level);
		QCURRENT = QCURRENT->next_queue;
	}
	printf("Room: %s links to room: %s END!		q addr: %p  level:%d\n\n", QCURRENT->parent_room->name, QCURRENT->current_room->name, QCURRENT, QCURRENT->current_room->level);
}

void			print_tqueue_path(t_obj *obj, t_room *temp)
{
	// printf("\n%s\n", __func__);
	if (temp != START_RM)
		print_tqueue_path(obj, temp->queue->parent_room);
	printf("Path to end room: %s\n", temp->name);
}

void			print_multiple_paths(t_obj *obj)
{
	printf("\n%s\n", __func__);
	t_room *temp;
	t_link *link;
	link = START_RM->start_link;

	while (link)
	{
		printf("start room: %s\n", START_RM->name);
		temp = link->room;
		while (temp)
		{
			printf("room: %s temp->queue:%p\n", temp->name, temp->queue);
			if (temp->queue && temp->queue->next_queue)
				temp = temp->queue->next_queue->current_room;
			else
				temp = NULL;
			
		}
		link = link->next;
	}
}
