/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/15 16:10:14 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

void			delete_string_lst(t_obj *obj, t_str **list)
{
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_string_lst(obj, &(*list)->next);
		ft_memdel((void*)&(*list)->str);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}


// using printf to print to screen
void			print_tstr_lst(t_obj *obj)
{
	printf("%s()\n", __func__);
	if (TSTR_L != NULL)
	{
		while (TSTR_L->next != NULL)
		{
			printf("addr:%p beginning:%p string:%s", TSTR_L, TSTR_L->beginning, (TSTR_L->str));
			TSTR_L = TSTR_L->next;
		}
			printf("addr:%p beginning:%p string:%s\n\n", TSTR_L, TSTR_L->beginning, (TSTR_L->str));
		TSTR_L = TSTR_L->beginning;
	}
}

void			print_troom_lst(t_obj *obj)
{
	CCURRENT = CSTART;
	printf("%s()\n", __func__);
	while (CCURRENT)
	{
		// printf("CCURRENT:%p, name:%s, coord_x:%d, coord_y:%d\nstart_rm:%p end_rm:%p\n", CCURRENT, CCURRENT->name, CCURRENT->coord_x, CCURRENT->coord_y, START_RM, END_RM);
		printf("CCURRENT:%p, name:%s, coord_x:%d, coord_y:%d\n", CCURRENT, CCURRENT->name, CCURRENT->coord_x, CCURRENT->coord_y);
		CCURRENT = CCURRENT->next;
	}
	printf("\n");
}

void			print_tlink_lst(t_obj *obj)
{
	printf("%s()\n", __func__);
	// obj->chain_current = obj->chain_start;
	// printf("\nobj->chain_current:%p\n", obj->chain_current);
	printf("Ants:%d\n", ANTS);
	CCURRENT = CSTART;
	while (CCURRENT)
	{
		// printf("ccurrent->links:%p ccurr->name:%s ccurr->links->start:%p ccurr->links->next:%p\n", CCURRENT->links, CCURRENT->name, CCURRENT->links->start, CCURRENT->links->next);
		// CCURRENT->links = CCURRENT->links->start;
		if (CCURRENT->links)
		{
			while (CCURRENT->links->next != NULL)
			{
				printf("Room: %s links to: %s\n", CCURRENT->name, CCURRENT->links->room->name);
				CCURRENT->links = CCURRENT->links->next;
			}
				printf("Room: %s links to: %s\n\n", CCURRENT->name, CCURRENT->links->room->name);
		}
		CCURRENT = CCURRENT->next;
	}
}