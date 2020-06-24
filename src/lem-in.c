/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/24 19:55:51 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"
#include <math.h>

int				main(void)
{
	t_obj 		obj;

	ft_bzero(&obj, sizeof(obj));
	// if (create_tstr_lst(&obj) && create_troom_lst(&obj) && \
	// 	create_tlink_lst(&obj) && check_duplicate_rooms_and_coordinates(&obj)\
	// 	&& remove_dead_end_paths(&obj, obj.chain_start, 0, 0, 0))
	init_lists_and_print(&obj);
	{
		// print_tstr_lst(&obj);
		connect_everything(&obj);
		assign_total_steps_to_paths(&obj);
		assign_min_ants_for_use_of_paths(&obj);
		print_multiple_paths(&obj);
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

void			connect_everything(t_obj *obj)
{
	double		steps;
	double		steps2;
	int			paths;
	int			combined_length_of_paths;

	breadth_first_search(obj);
	paths = 1;
	if (obj->q_end && obj->q_end->room == obj->end_room && obj->ants >= paths)
	{
		combined_length_of_paths = obj->q_end->level;
		steps = ceil((obj->ants - paths + combined_length_of_paths) / paths); // MUST REWRITE LINE
		steps2 = steps;
		assign_path(obj, obj->q_end);
		delete_tqueue_nodes(obj, obj->head_q);
		connect_tqueue_nodes(obj);
		// print_multiple_paths(obj);
	}
	else
	{
		// falls into else if qend is not endrm or ants are less than paths which could only be 1
		// ft_printf("first return\n");
		return ;
	}
	while (obj->ants >= paths)
	{
		breadth_first_search(obj);
		++paths;
		if (obj->q_end && obj->q_end->room == obj->end_room && obj->ants >= paths)
		{
			combined_length_of_paths += obj->q_end->level;
			steps = ceil((obj->ants - paths + combined_length_of_paths) / paths); // MUST REWRITE LINE
			if (steps < steps2)
			{
				assign_path(obj, obj->q_end);
				delete_tqueue_nodes(obj, obj->head_q);
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
		obj->start_room->links = obj->start_room->head_lnk;
		while (obj->start_room->links && paths)
		{
			if (obj->start_room->links->room->path && !obj->start_room->links->room->path->min_ants)
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



void			move_and_print_ants(t_obj *obj)
{
	t_room		*room;
	int			current_ant;
	int			end_rm_ants;
	int			ants_copy;

	ants_copy = obj->ants;
	current_ant = 1;
	end_rm_ants = 0;
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
				{
					ft_printf("L%d-%s ", room->ant, room->path->child_room->name);
					end_rm_ants += room->path->child_room == obj->end_room ? 1 : 0;
					room->path->child_room->ant = room->ant;
					room->ant = 0;
				}
				if (obj->ants && room->path->prnt_rm == obj->start_room)
				{
					if (room->path->min_ants <= obj->ants)
					{
						ft_printf("L%d-%s ", current_ant, room->name);
						room->ant = current_ant;
						--obj->ants;
						++current_ant;
					}
					break ;
				}
				room = room->path->prnt_rm;
			}
			obj->end_room->links = obj->end_room->links->next;
		}
		ft_putchar('\n');
	}
}

	// printf("line%d\n", __LINE__);
    // int ch;
    // while ((ch = getchar()) != '\n' && ch != EOF)
	// int		a;
	// int		b;
	// int		c;
	// int		d;
	// int		e;

	// a = create_tstr_lst(obj);
	// b = create_troom_lst(obj);
	// c = create_tlink_lst(obj);
	// d = check_duplicate_rooms_and_coordinates(obj);
	// e = remove_dead_end_paths(obj, obj->head_rm, 0, 0, 0);
	// printf("a: %d  b: %d  c: %d  d: %d  e: %d\n", a, b, c, d, e);
	// if (a && b && c && d && e)
int				init_lists_and_print(t_obj *obj)
{
	
	if (create_tstr_lst(obj) && create_troom_lst(obj) && \
		create_tlink_lst(obj) && check_duplicate_rooms_and_coordinates(obj) && \
		remove_dead_end_paths(obj, obj->head_rm, 0, 0, 0))
		{
			print_tstr_lst(obj);
			print_troom_lst(obj);
			print_tlink_lst(obj);
			// ft_printf("number of obj->end_room links:%d\n", count_links(obj->end_room->head_lnk));
			return (1);
		}
	delete_all(obj);
	return (0);
}
