/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/05/14 19:13:21 by macbook       ########   odam.nl         */
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
			// printf("addr:%p beginning:%p string:%s", TSTR_L, TSTR_STRT, (TSTR_L->str));
			ft_putstr(TSTR_L->str);
			TSTR_L = TSTR_L->next;
		}
			// printf("addr:%p beginning:%p string:%s\n\n", TSTR_L, TSTR_STRT, (TSTR_L->str));
		ft_putstr(TSTR_L->str);
		ft_putchar('\n');
		ft_putchar('\n');
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
	if (QSTART == NULL)
		return ;
	ROOM = QSTART->current_room;
	while (ROOM != QEND->current_room)
	{
		if (ROOM->queue && ROOM->queue->child_room)
			printf("parent room: %s links to current room: " C_BLUE "%s " C_RESET "next:%s	q addr: %p  level:%d\n", ROOM->queue->parent_room->name, ROOM->name, ROOM->queue->child_room->name, ROOM->queue, ROOM->level);
		ROOM = ROOM->queue->child_room;
	}
	printf("parent room: %s links to current room: %s next:%p	q addr: %p  level:%d\n", ROOM->queue->parent_room->name, ROOM->name, ROOM->queue->child_room, ROOM->queue, ROOM->level);
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
	t_room 		*room;
	t_link 		*links_startroom;

	links_startroom = START_RM->start_link;
	while (links_startroom)
	{
		room = links_startroom->room;
		// printf("name: %s room->queue:%p\n", room->name, room->queue);
		// printf("name: %s room->path:%p\n", room->name, room->path);
		if (room->path && room->path->parent_room == START_RM)
			printf("start room: %s\n", START_RM->name);
		while (room && room->path)
		{
			if (room->path && room->path->child_room)
			{
				printf("room: %s room->path:%p child_room:%s level:%d\n", room->name, room->path, room->path->child_room->name, room->path->level);

				room = room->path->child_room;
			}
			else
			{
				printf("end room: %s\n\n", room->name);
				room = NULL;
			}
		}
		links_startroom = links_startroom->next;
	}
}
