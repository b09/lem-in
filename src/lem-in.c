/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/05/24 20:36:41 by macbook       ########   odam.nl         */
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
		// solver(&obj);
		// solver(&obj);
		// solver(&obj);
		// solver(&obj);
		// solver(&obj);
		connect_everything(&obj);
		print_multiple_paths(&obj);
	}
	delete_all(&obj);
	return (0);
}

void			print_heuristic_level(t_obj *obj)
{
	int			level;
	t_link		*links;

	level = 0;
	links = END_RM->start_link;
	while (links)
	{
		printf(C_RED"\n%s()1: %d\n"C_RESET, __func__, level);
		if (links->room->path && links->room->path->level > 0)
			level += links->room->path->level;
		links = links->next;
		printf(C_RED"\n%s()2: %d\n"C_RESET, __func__, level);
	}
	printf(C_BLUE"\n%s(): %d\n"C_RESET, __func__, level);
}

int				solver(t_obj *obj)
{
	// printf("************\n\n");
	breadth_first_search(obj);
	// print_queue_from_qend(obj);
	// printf("%s() Line: %d\n\n", __func__, __LINE__);
	

	printf("end_rm->queue after bfs():%s path:%p queueu:%p\n", QEND->current_room->name, END_RM->path, END_RM->queue);
	if (QSTART)
	{
		// print_tqueue_lst(obj);

		printf("inside assign_path(), recursive\n");
		assign_path(obj, QEND);
		printf("\ndelete_tqueue_nodes()\n\n");
		delete_tqueue_nodes(obj, QSTART);

		printf("qend before connect_tqueue:%d\n", QEND->level);
		connect_tqueue_nodes(obj);//, QEND->current_room, 0);
		print_heuristic_level(obj);
		printf("qend after connect_tqueue:%p\n", QEND);
		// printf("\n");
		print_multiple_paths(obj);
	}
	return (1);
}
void			connect_everything(t_obj *obj)
{
	printf("inside %s\n", __func__);
	double		steps;
	double		steps2;
	// double		possible_steps;
	int			paths;
	int			combined_length_of_paths;

	paths = 1;
	breadth_first_search(obj);
	if (QEND && QEND->current_room == END_RM && ANTS >= paths)
	{
		// steps = QEND->level;
		combined_length_of_paths = QEND->level;
		steps = ceil((ANTS - paths + combined_length_of_paths) / paths);
		// possible_steps = steps;
		steps2 = steps;
		assign_path(obj, QEND);
		delete_tqueue_nodes(obj, QSTART);
		connect_tqueue_nodes(obj);
		print_multiple_paths(obj);
	}
	else
	{
		printf("first return\n");
		return ;
	}
	while (ANTS >= paths)
	{
		printf("paths:%d combined_length:%d steps:%f steps2:%f\n\n", paths, combined_length_of_paths, steps, steps2);
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
				print_multiple_paths(obj);
				steps2 = steps;
			}
			else
			{
				printf("second return steps:%f steps2:%f\n", steps, steps2);
				return ;
			}
		}
		else
		{
			printf("third return\n");
			return ;
		}
	}
}



int				init_lists_and_print(t_obj *obj)
{
	if (create_tstr_lst(obj) && create_troom_lst(obj) && \
		create_tlink_lst(obj) && check_duplicate_rooms_and_coordinates(obj))
		{
			print_tstr_lst(obj);
			// print_troom_lst(obj);
			print_tlink_lst(obj);
			printf("number of END_RM links:%d\n", count_links(END_RM->start_link));
			return (1);
		}
	delete_all(obj);
	return (0);
}


