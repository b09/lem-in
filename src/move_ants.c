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

static void		move_ant(t_lemin *lemin, t_room *start, t_ant *next)
{
	if (start->path && start->path->child_room)
	{
		move_ant(lemin, start->path->child_room, start->current_ant);
		if (next)
		{
			ft_printf("L%d-%s ", next->ant_id, start->name);
		}
		start->current_ant = next;
	}
	else if (!start->path)
	{
		if (start->current_ant)
		{
			lemin->ants_finished += 1;
			ft_printf("L%d-%s ", start->current_ant->ant_id, start->name);
			free(start->current_ant);
		}
		start->current_ant = next;
	}
}

void			print_move_ants
	(t_lemin *lemin, t_room *room, t_link *links_startroom)
{
	t_ant	*ant;
	int		ant_id;

	ant_id = 1;
	links_startroom = lemin->start_room->head_lnk;
	while (lemin->ants_finished < lemin->ants)
	{
		while (links_startroom)
		{
			room = links_startroom->room;
			if (room->path && room->path->prnt_rm == lemin->start_room)
			{
				if ((ant_id - 1) < lemin->ants
					&& (lemin->ants - (ant_id - 1) >= room->path->min_ants))
				{
					ant = ft_memalloc(sizeof(t_ant));
					// error if NULL?
					ant->ant_id = ant_id;
					ant_id += 1;
				}
				else
					ant = NULL;
				move_ant(lemin, room, ant);
			}
			links_startroom = links_startroom->next;
		}
		ft_printf("\n");
		links_startroom = lemin->start_room->head_lnk;
	}
}
