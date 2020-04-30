/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 17:41:22 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/28 20:31:42 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

void			delete_string_lst(t_str **list)
{
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_string_lst(&(*list)->next);
		ft_memdel((void*)&(*list)->str);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}

void			delete_troom_lst(t_room **list)
{
	if ((*list)->links)
		delete_tlink_lst(&(*list)->links);
	if ((*list)->path)
		ft_memdel((void*)&(*list)->path);
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_troom_lst(&(*list)->next);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}

void			delete_tlink_lst(t_link **list)
{
	if (*list)
	{
		if ((*list)->next)
			delete_tlink_lst(&(*list)->next);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}

void			delete_all(t_obj *obj)
{
	if (TSTR_L)
		delete_string_lst(&TSTR_L);
	if (CSTART)
		delete_troom_lst(&CSTART);
	exit(1);
}