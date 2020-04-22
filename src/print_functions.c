/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/22 17:48:40 by macbook       ########   odam.nl         */
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
	CCURRENT = CSTART;
	printf("%s()\n", __func__);
	while (CCURRENT)
	{
		// printf("CCURRENT:%p, name:%s, coord_x:%d, coord_y:%d\nstart_rm:%p end_rm:%p\n", CCURRENT, CCURRENT->name, CCURRENT->coord_x, CCURRENT->coord_y, START_RM, END_RM);
		printf("CCURRENT:%p, name:%s, coord_x:%d, coord_y:%d\n", CCURRENT, CCURRENT->name, CCURRENT->coord_x, CCURRENT->coord_y);
		CCURRENT = CCURRENT->next;
	}
	printf("\n");
}

void			print_tlink_lst(t_obj *obj)
{
	printf("%s()\n", __func__);
	CCURRENT = CSTART;
	while (CCURRENT)
	{
		if (CCURRENT->start_link)
		{
			CCURRENT->links = CCURRENT->start_link;
			while (CCURRENT->links->next != NULL)
			{
				printf("Room: %s links to: %s\n", CCURRENT->name, CCURRENT->links->room->name);
				CCURRENT->links = CCURRENT->links->next;
			}
			printf("Room: %s links to: %s\n\n", CCURRENT->name, CCURRENT->links->room->name);
		}
		CCURRENT = CCURRENT->next;
	}
	printf("exiting %s\n", __func__);
}


void			print_tqueue_lst(t_obj *obj)
{
	int 		i;
	i = 0;
	printf("%s()\n", __func__);
	QCURRENT = QSTART;
	while (QCURRENT != QEND)
	{
		printf("Room: %s links to room: %s		curr room addr: %p  level:%d\n", QCURRENT->parent_room->name, QCURRENT->current_room->name, QCURRENT->current_room, QCURRENT->current_room->level);
		QCURRENT = QCURRENT->next_queue;
	}
	printf("Room: %s links to room: %s END!		curr room addr: %p  level:%d\n", QCURRENT->parent_room->name, QCURRENT->current_room->name, QCURRENT->current_room, QCURRENT->current_room->level);
}

void			print_tqueue_path(t_obj *obj, t_room *temp)
{
	if (temp != START_RM)
		print_tqueue_path(obj, temp->queue->parent_room);
	printf("Path to end room: %s\n", temp->name);
}
