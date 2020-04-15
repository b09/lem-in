/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/15 18:38:50 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
main

*/

// t_room			*get_addr_by_name(char *str, t_obj *obj);
// void			create_tlink_node(t_room *link, t_room *room, char repeat);
// int				create_troom_node(t_obj *obj, int code);
// int				create_tlink_lst(t_obj *obj);
// int				create_troom_lst(t_obj *obj);
// int				validate_link(char *str);
// int				validate_comment(char *str);
// int				validate_string_list(char *str);
// void			populate_beginning_links_to_string_list(t_str *beginning_links, t_obj *obj); // make sure all lnkd_lists have members correctly assigned


int				main(void)
{
	t_obj 		obj;

	ft_bzero(&obj, sizeof(obj));
	create_tstr_lst(&obj);
	print_tstr_lst(&obj);
	obj.tstr_list = obj.tstr_list->beginning;
	create_troom_lst(&obj);
	print_troom_lst(&obj);
	create_tlink_lst(&obj);
	print_tlink_lst(&obj);
	delete_string_lst(&obj, &(obj.tstr_list));
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
