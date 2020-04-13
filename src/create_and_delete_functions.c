/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_and_delete_functions.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 16:47:57 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/13 22:48:27 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

void			delete_string_list(t_obj *obj, t_str **list)
{
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_string_list(obj, &(*list)->next);
		ft_memdel((void*)&(*list)->str);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}




void			copy_string_input(t_obj *obj)
{
	char		*str;
	t_str		*temp;

	temp = NULL;
	// every call to gnl() will change str's address
	// but each node will have a copy of every new
	// address that str has changed to
	gnl_with_newline(0, &str);
	if (str)
	{
		STR_L = malloc(sizeof(t_str));
		STR_L->str = str;
		STR_L->beginning = STR_L;
		STR_L->next = NULL;
		while (gnl_with_newline(0, &str) > 0)
		{
			temp = malloc(sizeof(t_str));
			temp->str = str;
			temp->beginning = STR_L->beginning;
			temp->next = NULL;
			STR_L->next = temp;
			STR_L = temp;
		}
		STR_L = STR_L->beginning;
	}
}

// using printf to print to screen
void			print_string_input(t_obj *obj)
{
	if (STR_L != NULL)
	{
		while (STR_L->next != NULL)
		{
			printf("addr:%p string:%s", STR_L, (STR_L->str));
			STR_L = STR_L->next;
		}
		STR_L = STR_L->beginning;
	}
	printf("STR_L:%p\n", STR_L);
}

void			print_links(t_obj *obj)
{
	obj->chain_current = obj->chain_start;
	printf("\n\nobj->chain_current:%p\n", obj->chain_current);
	printf("Ants:%d\n", ANTS);
	while (obj->chain_current && obj->chain_current->links)
	{
		printf("address of node in links: %p\n", obj->chain_current->links);
		obj->chain_current->links = obj->chain_current->links->next;
	}
}