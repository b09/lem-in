/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/09/11 20:40:39 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void			print_tstr_lst(t_lemin *lemin)
{
	lemin->tstr = lemin->head_tstr;
	if (lemin->tstr != NULL)
	{
		while (lemin->tstr->next != NULL)
		{
			ft_putstr(lemin->tstr->str);
			lemin->tstr = lemin->tstr->next;
		}
		ft_putstr(lemin->tstr->str);
		ft_putchar('\n');
		lemin->tstr = lemin->head_tstr;
	}
}

int				print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

void			print_multiple_paths
	(t_lemin *lemin, t_room *room, t_link *links_startroom)
{
	ft_printf("\n%s\n", __func__);
	links_startroom = lemin->start_room->head_lnk;
	while (links_startroom)
	{
		room = links_startroom->room;
		if (room->path && room->path->prnt_rm == lemin->start_room)
			ft_printf("start room: %s\n", lemin->start_room->name);
		while (room && room->path)
		{
			if (room->path && room->path->child_room)
			{
				ft_printf("room: %s room->path:%p child_room:%s level:%d"
		"total_steps_of_path:%d min_ants:%d\n", room->name, room->path,
		room->path->child_room->name, room->path->level, room->path->path_len,
		room->path->min_ants);
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
