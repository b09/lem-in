/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem_in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/28 20:35:09 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"
#include <math.h>

int				main(void)
{
	t_obj		obj;

	ft_bzero(&obj, sizeof(obj));
	if (create_tstr_lst(&obj) && create_troom_lst(&obj) &&\
		create_tlink_lst(&obj) && check_duplicate_rooms_and_coordinates(&obj)\
		&& remove_dead_end_paths(&obj, obj.head_rm, 0, 0))
	{
		connect_everything(&obj, 0, -1, 0);
		// print_tstr_lst(&obj);
		assign_total_steps_to_paths(&obj);
		assign_min_ants_for_use_of_paths(&obj, 1, 1, 0);
		move_and_print_ants(&obj, 1, 0, obj.ants);
		print_multiple_paths(&obj, 0, 0);
	}
	delete_all(&obj);
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

void			assign_total_steps_to_paths(t_obj *obj)
{
	t_room		*room;
	int			steps;

	steps = 0;
	room = NULL;
	obj->start_room->links = obj->start_room->head_lnk;
	while (obj->start_room->links)
	{
		if (obj->start_room->links->room->path)
		{
			room = obj->start_room->links->room;
			steps = 1;
			while (room != obj->end_room)
			{
				room = room->path->child_room;
				++steps;
			}
			obj->start_room->links->room->path->path_len = steps;
		}
		obj->start_room->links = obj->start_room->links->next;
	}
}

/*
**	no paths are protected in breadth_first_search(), even though in the func()
**	it appears they would fall into the else \n return;
*/

// THE ISSUE IS IN tail_q NOT HAVING ANY VALUE
void			connect_everything(t_obj *obj, double steps, double steps2,\
				int paths)
{
	int			length_of_paths;

	length_of_paths = 0;
	while (obj->ants >= paths)
	{
		breadth_first_search(obj, paths);
		++paths;
				printf("q_end: %p\n", obj->tail_q);

		if (obj->tail_q && obj->tail_q->room == obj->end_room &&\
		obj->ants >= paths)
		{
			printf("line:%d paths: %d\n", __LINE__, paths);
			length_of_paths += obj->tail_q->level;
			steps = ft_ceil((obj->ants - paths + length_of_paths) / paths);
			if (steps < steps2 || steps2 == -1)
			{
				assign_path(obj, obj->tail_q);
				delete_tqueue_nodes(obj, obj->head_q);
				connect_tqueue_nodes(obj);
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
**	each path. one the shortest path/s are found, start a counter from that
**	point which is when the first ants would reach the end. assign that
**	counter (which is one) to the path as the minimum number of ants requi-
**	red to use that path, and if multiple paths contain the same length,
**	assign the same number to them, but also increase that second counter
**	based on the number of current paths that can handle ants
*/

int				get_number_of_paths(t_obj *obj)
{
	int			paths;

	paths = 0;
	obj->start_room->links = obj->start_room->head_lnk;
	while (obj->start_room->links)
	{
		if (obj->start_room->links->room->path)
			++paths;
		obj->start_room->links = obj->start_room->links->next;
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

void			assign_min_ants_for_use_of_paths(t_obj *obj, int steps,\
int ants, int ant_counter)
{
	int			paths;

	paths = get_number_of_paths(obj);
	while (paths)
	{
		obj->start_room->links = obj->start_room->head_lnk;
		while (obj->start_room->links && paths)
		{
			if (obj->start_room->links->room->path &&\
			!obj->start_room->links->room->path->min_ants)
			{
				if (obj->start_room->links->room->path->path_len == steps)
				{
					obj->start_room->links->room->path->min_ants = ants;
					++ant_counter;
					--paths;
				}
			}
			obj->start_room->links = obj->start_room->links->next;
		}
		++steps;
		ants += ant_counter;
	}
}
