/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_ants.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 18:53:18 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/28 15:13:05 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static void		move_and_print_ants_helper_1(t_obj *obj, int *end_rm_ants,\
t_room *room)
{
	ft_printf("L%d-%s ", room->ant, room->path->child_room->name);
	*end_rm_ants += room->path->child_room == obj->end_room ? 1 : 0;
	room->path->child_room->ant = room->ant;
	room->ant = 0;
}

static void		move_and_print_ants_helper_2(t_obj *obj, int *current_ant,\
t_room *room)
{
	ft_printf("L%d-%s ", *current_ant, room->name);
	room->ant = *current_ant;
	--obj->ants;
	++(*current_ant);
}

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
			while (room->path)
			{
				if (room->ant)
					move_and_print_ants_helper_1(obj, &end_rm_ants, room);
				if (obj->ants && room->path->prnt_rm == obj->start_room)
				{
					if (room->path->min_ants <= obj->ants)
						move_and_print_ants_helper_2(obj, &current_ant, room);
					break ;
				}
				room = room->path->prnt_rm;
			}
			obj->end_room->links = obj->end_room->links->next;
		}
		ft_putchar('\n');
	}
}
