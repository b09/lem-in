/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/19 15:37:15 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"
#include <math.h>

int				main(void)
{
	t_obj 		obj;

	ft_bzero(&obj, sizeof(obj));
	if (init_lists_and_print(&obj))
	{
		connect_everything(&obj);
		assign_total_steps_to_paths(&obj);
		assign_min_ants_for_use_of_paths(&obj);
		// print_multiple_paths(&obj);
		move_and_print_ants(&obj);
	}
	delete_all(&obj);
	return (0);
}

void			assign_total_steps_to_paths(t_obj *obj)
{
	t_room 		*room;
	int			steps;

	steps = 0;
	room = NULL;
	START_RM->links = START_RM->start_link;
	while (START_RM->links)
	{
		if (START_RM->links->room->path)
		{
			room = START_RM->links->room;
			steps = 1;
			while (room != END_RM)
			{
				room = room->path->child_room;
				++steps;
			}
			START_RM->links->room->path->path_total_steps = steps;
		}
		START_RM->links = START_RM->links->next;
	}
}

void			connect_everything(t_obj *obj)
{
	double		steps;
	double		steps2;
	int			paths;
	int			combined_length_of_paths;

	breadth_first_search(obj);
	paths = 1;
	if (QEND && QEND->current_room == END_RM && ANTS >= paths)
	{
		combined_length_of_paths = QEND->level;
		steps = ceil((ANTS - paths + combined_length_of_paths) / paths); // MUST REWRITE LINE
		steps2 = steps;
		assign_path(obj, QEND);
		delete_tqueue_nodes(obj, QSTART);
		connect_tqueue_nodes(obj);
		// print_multiple_paths(obj);
	}
	else
	{
		// falls into else if qend is not endrm or ants are less than paths which could only be 1
		// ft_printf("first return\n");
		return ;
	}
	while (ANTS >= paths)
	{
		breadth_first_search(obj);
		++paths;
		if (QEND && QEND->current_room == END_RM && ANTS >= paths)
		{
			combined_length_of_paths += QEND->level;
			steps = ceil((ANTS - paths + combined_length_of_paths) / paths);
			if (steps < steps2)
			{
				assign_path(obj, QEND);
				delete_tqueue_nodes(obj, QSTART);
				connect_tqueue_nodes(obj);
				// print_multiple_paths(obj);
				steps2 = steps;
			}
			else
			{
				// ft_printf("second return steps:%f steps2:%f\n", steps, steps2);
				return ;
			}
		}
		else
		{
			// ft_printf("third return\n");
			return ;
		}
	}
}

/*
**	ensure the length of each path is in the path->path_total_steps member
**	create a while loop that starts at 1, and checks path_total_steps for
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
	START_RM->links = START_RM->start_link;
	while (START_RM->links)
	{
		if (START_RM->links->room->path)
			++paths;
		START_RM->links = START_RM->links->next;
	}
	return (paths);
}

void			assign_min_ants_for_use_of_paths(t_obj *obj)
{
	int			steps;
	int			ants;
	int			ant_counter;
	int			paths;

	steps = 1;
	ants = 1;
	ant_counter = 0;
	paths = get_number_of_paths(obj);
	while (paths)
	{
		START_RM->links = START_RM->start_link;
		while (START_RM->links && paths)
		{
			if (START_RM->links->room->path && !START_RM->links->room->path->min_ants)
			{
				if (START_RM->links->room->path->path_total_steps == steps)
				{
					START_RM->links->room->path->min_ants = ants;
					++ant_counter;
					--paths;
				}
			}
			START_RM->links = START_RM->links->next;
		}
		++steps;
		ants += ant_counter;
	}
}

int				init_lists_and_print(t_obj *obj)
{
	if (create_tstr_lst(obj) && create_troom_lst(obj) && \
		create_tlink_lst(obj) && check_duplicate_rooms_and_coordinates(obj))
		{
			print_tstr_lst(obj);
			print_troom_lst(obj);
			print_tlink_lst(obj);
			ft_printf("number of END_RM links:%d\n", count_links(END_RM->start_link));
			return (1);
		}
	delete_all(obj);
	return (0);
}

void			move_and_print_ants(t_obj *obj)
{
	t_room		*room;
	int			current_ant;
	int			end_rm_ants;
	int			ants_copy;

	ants_copy = ANTS;
	current_ant = 1;
	end_rm_ants = 0;
	room = NULL;

	while (end_rm_ants < ants_copy)
	{
		END_RM->links = END_RM->start_link;
		while (END_RM->links && END_RM->links->room)
		{
			room = END_RM->links->room;
			while (room->path)
			{
				if (room->ant)
				{
					ft_printf("L%d-%s ", room->ant, room->path->child_room->name);
					end_rm_ants += room->path->child_room == END_RM ? 1 : 0;
					room->path->child_room->ant = room->ant;
					room->ant = 0;
				}
				if (ANTS && room->path->parent_room == START_RM)
				{
					if (room->path->min_ants <= ANTS)
					{
						ft_printf("L%d-%s ", current_ant, room->name);
						room->ant = current_ant;
						--ANTS;
						++current_ant;
					}
					break ;
				}
				room = room->path->parent_room;
			}
			END_RM->links = END_RM->links->next;
		}
		ft_putchar('\n');
	}
}

// void			check_paths_for_ants(t_obj *obj, int *end_rm_ants, int *current_ant)
// {
// 	while (room->path)
// 	{
// 		if (room->ant)
// 		{
// 			ft_printf("L%d-%s ", room->ant, room->path->child_room->name);
// 			end_rm_ants += room->path->child_room == END_RM ? 1 : 0;
// 			room->path->child_room->ant = room->ant;
// 			room->ant = 0;
// 		}
// 		if (ANTS && room->path->parent_room == START_RM)
// 		{
// 			if (room->path->min_ants <= ANTS)
// 			{
// 				ft_printf("L%d-%s ", current_ant, room->name);
// 				room->ant = current_ant;
// 				--ANTS;
// 				++current_ant;
// 			}
// 			break ;
// 		}
// 		room = room->path->parent_room;
// 	}
// }
