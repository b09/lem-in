/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_duplicates.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 15:09:20 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/28 15:09:43 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

int				check_duplicate_coordinates(t_obj *obj)
{
	t_room		*temp;

	temp = obj->head_rm;
	while (temp)
	{
		obj->room = temp->next;
		while (obj->room && temp)
		{
			if (obj->room->coord_x == temp->coord_x)
			{
				if (obj->room->coord_y == temp->coord_y)
					return (print_error(DUP_COOR));
			}
			obj->room = obj->room->next;
		}
		temp = temp->next;
	}
	return (1);
}

int				check_duplicate_rooms_and_coordinates(t_obj *obj)
{
	t_room		*temp;

	temp = obj->head_rm;
	while (temp)
	{
		obj->room = temp->next;
		while (obj->room && temp)
		{
			if (ft_strcmp(obj->room->name, temp->name) == 0)
				return (print_error(DUP_NAME));
			obj->room = obj->room->next;
		}
		temp = temp->next;
	}
	return (check_duplicate_coordinates(obj));
}
