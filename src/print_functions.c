/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/21 18:40:50 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

// using ft_printf to print to screen
void			print_tstr_lst(t_obj *obj)
{
	TSTR_L = TSTR_STRT;
	if (TSTR_L != NULL)
	{
		while (TSTR_L->next != NULL)
		{
			// ft_printf("addr:%p beginning:%p string:%s", TSTR_L, TSTR_STRT, (TSTR_L->str));
			ft_putstr(TSTR_L->str);
			TSTR_L = TSTR_L->next;
		}
			// ft_printf("addr:%p beginning:%p string:%s\n\n", TSTR_L, TSTR_STRT, (TSTR_L->str));
		ft_putstr(TSTR_L->str);
		ft_putchar('\n');
		ft_putchar('\n');
		TSTR_L = TSTR_STRT;
	}
}

void			print_troom_lst(t_obj *obj)
{
	ROOM = CSTART;
	ft_printf("%s()\n", __func__);
	while (ROOM)
	{
		// ft_printf("ROOM:%p, name:%s, coord_x:%d, coord_y:%d\nstart_rm:%p end_rm:%p\n", ROOM, ROOM->name, ROOM->coord_x, ROOM->coord_y, START_RM, END_RM);
		ft_printf("ROOM:%p, name:%s, coord_x:%d, coord_y:%d dead_end:%d\n", ROOM, ROOM->name, ROOM->coord_x, ROOM->coord_y, ROOM->dead_end);
		ROOM = ROOM->next;
	}
	ft_printf("\n");
}

void			print_tlink_lst(t_obj *obj)
{
	ft_printf("%s()\n", __func__);
	ROOM = CSTART;
	while (ROOM)
	{
		if (ROOM->start_link)
		{
			ROOM->links = ROOM->start_link;
			while (ROOM->links->next != NULL)
			{
				ft_printf("Room: %s links to: %s\n", ROOM->name, ROOM->links->room->name);
				ROOM->links = ROOM->links->next;
			}
			ft_printf("Room: %s links to: %s\n\n", ROOM->name, ROOM->links->room->name);
		}
		ROOM = ROOM->next;
	}
	// ft_printf("exiting %s\n", __func__);
}


void			print_tqueue_lst(t_obj *obj)
{
	int 		i;
	i = 0;
	ft_printf("%s()\n", __func__);
	if (QSTART == NULL)
		return ;
	ROOM = QSTART->current_room;
	while (ROOM != QEND->current_room)
	{
		if (ROOM->queue && ROOM->queue->child_room)
			ft_printf("parent room: %s links to current room: " C_BLUE "%s " C_RESET "next:%s	q addr: %p  level:%d\n", ROOM->queue->parent_room->name, ROOM->name, ROOM->queue->child_room->name, ROOM->queue, ROOM->level);
		ROOM = ROOM->queue->child_room;
	}
	ft_printf("parent room: %s links to current room: %s next:%p	q addr: %p  level:%d\n", ROOM->queue->parent_room->name, ROOM->name, ROOM->queue->child_room, ROOM->queue, ROOM->level);
}


void			print_tqueue_path(t_obj *obj, t_room *temp)
{
	// ft_printf("\n%s\n", __func__);
	if (temp != START_RM)
		print_tqueue_path(obj, temp->queue->parent_room);
	ft_printf("Path to end room: %s\n", temp->name);
}

void			print_multiple_paths(t_obj *obj)
{
	ft_printf("\n%s\n", __func__);
	t_room 		*room;
	t_link 		*links_startroom;

	links_startroom = START_RM->start_link;
	while (links_startroom)
	{
		room = links_startroom->room;
		// ft_printf("name: %s room->queue:%p\n", room->name, room->queue);
		// ft_printf("name: %s room->path:%p\n", room->name, room->path);
		if (room->path && room->path->parent_room == START_RM)
			ft_printf("start room: %s\n", START_RM->name);
		while (room && room->path)
		{
			if (room->path && room->path->child_room)
			{
				ft_printf("room: %s room->path:%p child_room:%s level:%d total_steps_of_path:%d min_ants:%d\n", room->name, room->path, room->path->child_room->name, room->path->level, room->path->path_total_steps, room->path->min_ants);

				room = room->path->child_room;
			}
			else
			{
				ft_printf("end room: %s\n\n", room->name);
				room = NULL;
			}
		}
		links_startroom = links_startroom->next;
	}
}

void			print_heuristic_level(t_obj *obj)
{
	int			level;
	t_link		*links;

	level = 0;
	links = END_RM->start_link;
	while (links)
	{
		ft_printf(C_RED"\n%s()1: %d\n"C_RESET, __func__, level);
		if (links->room->path && links->room->path->level > 0)
			level += links->room->path->level;
		links = links->next;
		ft_printf(C_RED"\n%s()2: %d\n"C_RESET, __func__, level);
	}
	ft_printf(C_BLUE"\n%s(): %d\n"C_RESET, __func__, level);
}
