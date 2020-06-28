/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/28 19:08:37 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void			print_tstr_lst(t_obj *obj)
{
	obj->tstr = obj->head_tstr;
	if (obj->tstr != NULL)
	{
		while (obj->tstr->next != NULL)
		{
			ft_putstr(obj->tstr->str);
			obj->tstr = obj->tstr->next;
		}
		ft_putstr(obj->tstr->str);
		ft_putchar('\n');
		obj->tstr = obj->head_tstr;
	}
}

void			print_troom_lst(t_obj *obj)
{
	ft_printf("%s()\n", __func__);
	obj->room = obj->head_rm;
	while (obj->room)
	{
		ft_printf("obj->room:%p, name:%s, coord_x:%d, coord_y:%d dead_end:%d\n"\
		, obj->room, obj->room->name, obj->room->coord_x, obj->room->coord_y,\
		obj->room->dead_end);
		obj->room = obj->room->next;
	}
	ft_printf("\n");
}

void			print_tlink_lst(t_obj *obj)
{
	ft_printf("%s()\n", __func__);
	obj->room = obj->head_rm;
	while (obj->room)
	{
		if (obj->room->head_lnk)
		{
			obj->room->links = obj->room->head_lnk;
			while (obj->room->links->next != NULL)
			{
				ft_printf("Room: %s links to: %s\n", obj->room->name,\
				obj->room->links->room->name);
				obj->room->links = obj->room->links->next;
			}
			ft_printf("Room: %s links to: %s\n\n", obj->room->name,\
			obj->room->links->room->name);
		}
		obj->room = obj->room->next;
	}
}

void			print_tqueue_lst(t_obj *obj)
{
	int			i;

	i = 0;
	ft_printf("%s()\n", __func__);
	if (obj->head_q == NULL)
		return ;
	obj->room = obj->head_q->room;
	while (obj->room != obj->tail_q->room)
	{
		if (obj->room->queue && obj->room->queue->child_room)
			ft_printf("parent room: %s links to current room: " C_BLUE "%s "\
			C_RESET "next:%s	q addr: %p  level:%d\n",\
			obj->room->queue->prnt_rm->name, obj->room->name,\
			obj->room->queue->child_room->name, obj->room->queue,\
			obj->room->level);
		obj->room = obj->room->queue->child_room;
	}
	ft_printf("parent room: %s links to current room: %s next:%p	q addr: %p \
	level:%d\n", obj->room->queue->prnt_rm->name, obj->room->name,\
	obj->room->queue->child_room, obj->room->queue, obj->room->level);
}

void			print_tqueue_path(t_obj *obj, t_room *temp)
{
	if (temp != obj->start_room)
		print_tqueue_path(obj, temp->queue->prnt_rm);
	ft_printf("Path to end room: %s\n", temp->name);
}

void			print_multiple_paths(t_obj *obj, t_room *room,\
t_link *links_startroom)
{
	ft_printf("\n%s\n", __func__);
	links_startroom = obj->start_room->head_lnk;
	while (links_startroom)
	{
		room = links_startroom->room;
		if (room->path && room->path->prnt_rm == obj->start_room)
			ft_printf("start room: %s\n", obj->start_room->name);
		while (room && room->path)
		{
			if (room->path && room->path->child_room)
			{
				ft_printf("room: %s room->path:%p child_room:%s level:%d\
				total_steps_of_path:%d min_ants:%d\n", room->name, room->path,\
				room->path->child_room->name, room->path->level,\
				room->path->path_len, room->path->min_ants);
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
	links = obj->end_room->head_lnk;
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

void			print_queue_from_qend(t_obj *obj)
{
	t_queue		*queue;

	ft_printf("%s()\n", __func__);
	queue = obj->head_q;
	while (queue)
	{
		queue->room && ft_printf("level: %d current room:%s ", queue->level,\
		queue->room->name);
		queue->prnt_rm && ft_printf("parent: %s ", queue->prnt_rm->name);
		queue->child_room && ft_printf("child: %s ", queue->child_room->name);
		ft_printf("\n");
		if (queue == obj->curr_q)
			ft_printf(C_BLUE"	^^^^^ QHEAD ^^^^\n"C_RESET);
		queue = queue->next;
	}
	ft_printf("\n");
}

int				print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
