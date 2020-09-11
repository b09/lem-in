/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/09/11 20:40:39 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void			print_tstr_lst(t_obj *obj)
{
	obj->tstr = obj->head_tstr;
	if (obj->tstr != NULL)
	{
		while (obj->tstr->next != NULL)
		{
			ft_putstr(obj->tstr->str);
			obj->tstr = obj->tstr->next;
		}
		ft_putstr(obj->tstr->str);
		ft_putchar('\n');
		obj->tstr = obj->head_tstr;
	}
}

int				print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
