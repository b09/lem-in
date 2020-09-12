/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem_in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/09/11 20:25:36 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"
#include <math.h>

int				main(int argc, const char *argv[])
{
	t_lemin		lemin;
	int			fd;

	fd = 0;
	if (argc >= 2)
		fd = open(argv[1], O_RDONLY);

	ft_bzero(&lemin, sizeof(lemin));
	if (create_tstr_lst(&lemin, fd >= 0 ? fd : 0)
		&& create_troom_lst(&lemin)
		&& create_tlink_lst(&lemin)
		&& check_duplicate_rooms_and_coordinates(&lemin)
		&& remove_dead_end_paths(&lemin, lemin.head_rm, 0, 0))
	{
		connect_everything(&lemin, 0, -1, 0);
		print_tstr_lst(&lemin);
		assign_total_steps_to_paths(&lemin);
		assign_min_ants_for_use_of_paths(&lemin, 1, 1, 0);
		print_multiple_paths(&lemin, NULL, NULL);
//		move_and_print_ants(&lemin, 1, 0, lemin.ants);
		print_move_ants(&lemin, NULL, NULL);
	}
	delete_all(&lemin);
	return (0);
}

/*
**	all paths will go through rooms that link to startroom, and because of this,
**	if any of those rooms are on a path, the length of that path will be
**	calculated and assigned to the room. this number will be used later on by
**	a function which will dispath ants by iterating through the rooms that
**	connect to the start_room and checking if the path is suitable for an ant
**	based on the number of ants remaining in the start, and the length of each
**	path
*/

void			assign_total_steps_to_paths(t_lemin *lemin)
{
	t_room		*room;
	int			steps;

	room = NULL;
	lemin->start_room->links = lemin->start_room->head_lnk;
	while (lemin->start_room->links)
	{
		if (lemin->start_room->links->room->path)
		{
			room = lemin->start_room->links->room;
			steps = 1;
			while (room != lemin->end_room)
			{
				room = room->path->child_room;
				++steps;
			}
			lemin->start_room->links->room->path->path_len = steps;
		}
		lemin->start_room->links = lemin->start_room->links->next;
	}
}

/*
**	no paths are protected in breadth_first_search(), even though in the func()
**	it appears they would fall into the else \n return;
*/

void			connect_everything
	(t_lemin *lemin, double steps, double steps2, int paths)
{
	int			length_of_paths;

	length_of_paths = 0;
	while (lemin->ants >= paths)
	{
		breadth_first_search(lemin, paths);
		++paths;
		if (lemin->tail_q && lemin->tail_q->room == lemin->end_room
			&& lemin->ants >= paths)
		{
			length_of_paths += lemin->tail_q->level;
			steps = ft_ceil((lemin->ants - paths + length_of_paths) / paths);
			if (steps < steps2 || steps2 == -1)
			{
				assign_path(lemin, lemin->tail_q);
				delete_tqueue_nodes(lemin, lemin->head_q, 0);
				connect_tqueue_nodes(lemin);
			}
			else
				return ;
			steps2 = steps;
		}
		else
			return ;
	}
}

/*
**	ensure the length of each path is in the path->path_len member
**	create a while loop that starts at 1, and checks path_len for
**	each path. once the shortest *path/s are found, start a counter from that
**	point which is when the first ants would reach the end. assign that
**	counter (which is one) to the path as the minimum number of ants requi-
**	red to use that path, and if multiple paths contain the same length,
**	assign the same number to them, but also increase that second counter
**	based on the number of current paths that can handle ants
**
**		notes: *path/s == multiple paths could have the same length
**						so there could be multiple shortest paths
*/

int				get_number_of_paths(t_lemin *lemin)
{
	int			paths;

	paths = 0;
	lemin->start_room->links = lemin->start_room->head_lnk;
	while (lemin->start_room->links)
	{
		if (lemin->start_room->links->room->path)
			++paths;
		lemin->start_room->links = lemin->start_room->links->next;
	}
	return (paths);
}

/*
**	Ants are dispatched down paths, and as their numbers decrease from the start
**	room, choosing the correct path (which may or may not be the shortest of the
**	available paths) is important. The below func() will assign a number to a
**	path which represents the minimum number of ants that should still be in the
**	startroom in order to dispath an ant on said path.
*/

void			assign_min_ants_for_use_of_paths
	(t_lemin *lemin, int steps, int ants, int ant_counter)
{
	int			paths;

	paths = get_number_of_paths(lemin);
	while (paths)
	{
		lemin->start_room->links = lemin->start_room->head_lnk;
		while (lemin->start_room->links && paths)
		{
			if (lemin->start_room->links->room->path &&\
			!lemin->start_room->links->room->path->min_ants)
			{
				if (lemin->start_room->links->room->path->path_len == steps)
				{
					lemin->start_room->links->room->path->min_ants = ants;
					++ant_counter;
					--paths;
				}
			}
			lemin->start_room->links = lemin->start_room->links->next;
		}
		++steps;
		ants += ant_counter;
	}
}
