/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/05/14 18:59:30 by macbook       ########   odam.nl         */
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
		// solver(&obj);
		// solver(&obj);
	}
	delete_all(&obj);
	return (0);
}

int				solver(t_obj *obj)
{
	// printf("************\n\n");
	breadth_first_search(obj);
	print_queue_from_qend(obj);
	printf("%s() Line: %d\n\n", __func__, __LINE__);
	

	printf("end_rm->queue after bfs():%s path:%p queueu:%p\n", QEND->current_room->name, END_RM->path, END_RM->queue);
	if (QSTART)
	{
		// print_tqueue_lst(obj);

		printf("inside assign_path(), recursive\n");
		assign_path(obj, QEND);
		printf("\ndelete_tqueue_nodes()\n\n");
		delete_tqueue_nodes(obj, QSTART);

		connect_tqueue_nodes(obj);//, QEND->current_room, 0);
		// printf("\n");
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
			// print_troom_lst(obj);
			print_tlink_lst(obj);
			printf("number of END_RM links:%d\n", count_links(END_RM->start_link));
			return (1);
		}
	delete_all(obj);
	return (0);
}


