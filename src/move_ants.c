/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_ants.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 18:53:18 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/11 20:37:01 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static void		move_and_print_ants_helper_1(t_obj *obj, int *end_rm_ants,\
t_room *room)
{
	ft_printf("L%d-%s ", room->ant, room->path->child_room->name);
	if (room != obj->end_room)
	{
		*end_rm_ants += (room->path->child_room == obj->end_room) ? 1 : 0;
		room->path->child_room->ant = room->ant;
		room->ant = 0;
	}
}

/*
**	the starting number of ants reflected in obj->ants. as those ants 'leave'
**	start_room, obj->ants get decreased, and also as the 'current_ant' counter
**	equally increases, so that L1, L2 ....L13, can be printed. value of ant, for
**	example 40, is passed from room to room, and that value will be unique, so
**	only one room can ever have that value.
*/

static void		move_and_print_ants_helper_2(t_obj *obj, int *current_ant,\
t_room *room)
{
	ft_printf("L%d-%s ", *current_ant, room->name);
	room->ant = *current_ant;
	obj->ants--;
	++(*current_ant);
}

static void		move_and_print_ants_helper_3(t_obj *obj, t_room *room, int
*end_rm_ants, int *current_ant)
{
	while (room->path)
	{
		if (room->ant)
			move_and_print_ants_helper_1(obj, end_rm_ants, room);
		if (obj->ants && room->path->prnt_rm == obj->start_room &&
		room->path->min_ants <= obj->ants)
		{
			move_and_print_ants_helper_2(obj, current_ant, room);
			return ;
		}
		room = room->path->prnt_rm;
	}
}

/*
**	func() will print ants from end to start, as ants that are farthest down the
**	path must be printed and moved first. 
**
**	while all ants are not in the end
**	iterate through rooms that link to end room
**	if any individual room of those rooms are on a path
**		if ant in room
**			print name of next room with ant number
**			move ant into next room
**			if next room is end_room, increase the count of end_room ants
**			and assign 0 to current room->ant
**		if parent room of current room is start room and there are ants remainin
**			add ant to path, decrease ants that remain, increase 'current_ant'
*/

void			move_and_print_ants(t_obj *obj, int current_ant,\
int end_rm_ants, int ants_copy)
{
	t_room		*room;
	
	room = NULL;
	while (end_rm_ants < ants_copy)
	{
		obj->end_room->links = obj->end_room->head_lnk;
		while (obj->end_room->links && obj->end_room->links->room)
		{
			room = obj->end_room->links->room;
			move_and_print_ants_helper_3(obj, room, &end_rm_ants, &current_ant);
			obj->end_room->links = obj->end_room->links->next;
		}
		ft_putchar('\n');
	}
}
