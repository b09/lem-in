/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/27 20:17:32 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

int				main(void)
{
	t_obj 		obj;

	ft_bzero(&obj, sizeof(obj));
	if (init_lists_and_print(&obj))
	{
		printf("************\n\n");
		create_tqueue_lst(&obj);
		print_tqueue_lst(&obj);
		printf("print_tqueue_path()\n\n");
		print_tqueue_path(&obj, obj.q_end->current_room);

		assign_path(&obj, obj.q_end->current_room);
		printf("\ndelete_tqueue_path()\n\n");
		delete_tqueue_nodes(&obj, &(obj.q_start));
		connect_tqueue_nodes(&obj, (obj.q_end));
		printf("\n");
		print_tqueue_lst(&obj);

		obj.q_start = 0;

		

		// create_tqueue_lst(&obj);
		// print_tqueue_lst(&obj);
		// printf("\n\ncomplete!\n");
	}
	delete_all(&obj);
	return (0);
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




/*
**	every t_str node has a t_str *beginning_links member which is at first NULL
**	this func() iterates through the t_str linked list and assigns
**	beginning_links to every node in the list
*/
// void			populate_beginning_links_to_string_list(t_str *beginning_links, t_obj *obj) // make sure all lnkd_lists have members correctly assigned
// {
// 	TSTR_L = TSTR_L->beginning;
// 	while (TSTR_L && TSTR_L->next != NULL)
// 	{
// 		TSTR_L->beginning_links = beginning_links;
// 		TSTR_L = TSTR_L->next;
// 	}
// 	TSTR_L->beginning_links = beginning_links;
// 	TSTR_L = TSTR_L->beginning;
// }
