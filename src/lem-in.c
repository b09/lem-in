/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/30 20:10:15 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

int				main(void)
{
	t_obj 		obj;

	ft_bzero(&obj, sizeof(obj));
	if (init_lists_and_print(&obj))
	{
		solver(&obj);
		solver(&obj);
		solver(&obj);
	}
	delete_all(&obj);
	return (0);
}

int				solver(t_obj *obj)
{
	printf("************\n\n");
	breathe_first_search(obj);
	printf("end_rm->queue after bfs():%p path:%p\n", END_RM->queue, END_RM->path);
	if (QSTART)
	{
		print_tqueue_lst(obj);

		assign_path(obj, obj->q_end->current_room);
		printf("\ndelete_tqueue_nodes()\n\n");
		delete_tqueue_nodes(obj, (obj->q_start->current_room));

		connect_tqueue_nodes(obj, (obj->q_end->current_room), 0);
		printf("\n");
		print_multiple_paths(obj);
	}
	return (1);
}



int				init_lists_and_print(t_obj *obj)
{
	if (create_tstr_lst(obj) && create_troom_lst(obj) && \
		create_tlink_lst(obj) && check_duplicate_rooms_and_coordinates(obj))
		{
			print_tstr_lst(obj);
			print_troom_lst(obj);
			print_tlink_lst(obj);
			return (1);
		}
	delete_all(obj);
	return (0);
}


