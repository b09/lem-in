/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/14 20:57:26 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
main
	copy_string_input
	print_string_input
	delete_string_input



	get_input
		validate_string
			validate_links
		create_lnkd_list
*/

t_room			*get_address_of_room_by_name(char *str, t_obj *obj);
void			create_t_link_node(t_room *link, t_room *room, char repeat);
int				assign_links_to_rooms(t_obj *obj);
int				validate_link(char *str);
int				validate_rooms_from_string(t_obj *obj);
int				validate_comment(char *str);
int				validate_string_list(char *str);
int				create_room_node(t_obj *obj, int code);
int				assign_input_to_obj(t_obj *obj);
void			populate_beginning_links_to_string_list(t_str *beginning_links, t_obj *obj); // make sure all lnkd_lists have members correctly assigned


int				main(void)
{
    // get content from stdin with gnl
	// first line: number of ants
	// when ##start encountered, next line is start
	// when ##end encountered, next line is end
	// lines containing one # are ignored
	t_obj obj;
	ft_bzero(&obj, sizeof(obj));
	copy_string_input(&obj);
	print_string_input(&obj);
	// print_string_input(&obj);
	obj.string_list = obj.string_list->beginning;
	assign_input_to_obj(&obj);
	print_rooms(&obj);
	assign_links_to_rooms(&obj);
	print_links(&obj);

	// create_lnkd_list(&obj);
	delete_string_list(&obj, &(obj.string_list));


	// iterate through string_list to validate data
	// populate t_room list with data from string_list
	// read data from string_list

}






t_room			*get_address_of_room_by_name(char *str, t_obj *obj)
{
	t_room		*temp;
	
	temp = CSTART;
	while (temp)
	{
		if (!ft_memcmp(temp->name, str, ft_strlen(temp->name)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}


void			create_t_link_node(t_room *link, t_room *room, char repeat)
{
	t_links		*new_node;

	if (link == room)
		return ;
	new_node = ft_memalloc(sizeof(t_links));
	new_node->room = link;
	new_node->next = NULL;
	if (room->links == NULL)
	{
		room->links = new_node;
		room->links->start = new_node;
		room->links->current = new_node;
	}
	else
	{
		room->links->current->next = new_node;
		room->links->current = new_node;
	}
	if (repeat)
		create_t_link_node(room, link, 0);
}


/*
	iterate thru string list starting from string that
	is not a string describing rooms, just links
*/
int				validate_link(char *str)
{
	int			i;
	int			dash;

	i = 0;
	dash = 0;
	while (str[i])
	{
		if ((!ft_isprint(str[i]) && str[i] != '-' && str[i] != '\n') || (i == 0 && str[i] == '-'))
			return (0);
		if (str[i] == '-')
			++dash;
		++i;
	}
	if (dash > 1)
		return (0);
	return (5);
}

// check strings with first character '#', which could be command or comment
int				validate_comment(char *str)
{
	if (ft_strcmp(str, "##start\n") == 0)
		return (2);
	else if (ft_strcmp(str, "##end\n") == 0)
		return (3);
	else
		return (4);
}

/*
// ensure that original input is validated
// returns:
	0
	1 = valid first string
	2 = start
	3 = end
	4 = normal comment, ignore
*/
int				validate_string_list(char *str)
{
	int			i;
	int			spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		// check if everything is a printable char, and not ' ' as first character
		if (str[i] != '\n' && (!ft_isprint(str[i]) || (i == 0 && str[i] == ' ')))
		{
			ft_putstr_fd("Error, invalid character in line\n", 0);
			return (0);
		}

		// validate str if comment found, return 
		if (str[i] == '#' && i == 0)
			return (validate_comment(str));

		// only two spaces should exist per line
		if (str[i] == ' ')
		{
			++spaces;
			++i;
		}
		// coordinates will be digits after room name: name coord_x coord_y
		if (spaces > 0 && !ft_isdigit(str[i]) && str[i] != '\n')
		{
			ft_putstr_fd("Error, coordinate is not a digit\n", 0);
			return (0);
		}
		++i;
	}
	// every line should have two spaces or should be a str describing links between rooms
	if (spaces != 2)
		return (validate_link(str));
	return (1);
}


/*
	called in:
		assign_input_to_obj()

	temp->name is malloced; must be freed at end of program
	t_room node created and assignment of:
		name
		coord_x
		coord_y

	assignment of node into linked list contained in t_obj obj
*/
int				create_room_node(t_obj *obj, int code)
{
	t_room		*temp;
	int			i;

	i = 0;
	temp = ft_memalloc(sizeof(t_room));
	while (STR[i] && STR[i] != ' ')
		++i;
	temp->name = ft_strnew(i);
	temp->name = ft_memcpy(temp->name, STR, i);
	i += STR[i] == ' ' ? 1 : 0; // for space in string
	temp->coord_x = ft_atoi(&STR[i]);
	while (STR[i] && ft_isdigit(STR[i]))
		++i;
	i += STR[i] == ' ' ? 1 : 0; // for space in string
	temp->coord_y = ft_atoi(&STR[i]);
	temp->next = NULL;
	temp->previous = NULL;
	if (CSTART == NULL)
	{
		CSTART = temp;
		CCURRENT = temp;
	}
	else
	{
		CEND->next = temp;
		temp->previous = CEND;
	}
	if (code == 2)
		START_RM = CCURRENT;
	else if (code == 3)
		END_RM = CCURRENT;
	CEND = temp;
	return (1);
}

int				assign_links_to_rooms(t_obj *obj)
{
	t_str 		*copy;
	t_room 		*temp;
	while (STR_L && STR_L->next != NULL && validate_link(STR))
		STR_L = STR_L->next;
	if (STR_L->next != NULL && !validate_link(STR))
		return (0);
	CCURRENT = CSTART;
	while (CCURRENT != NULL)
	{
		STR_L = STR_L->beginning_links;
		while (STR_L)
		{
			if (ft_strnstr(STR, CCURRENT->name, ft_strlen(STR)))
			{
				// go one char beyond '-' in STR to get name of
				// room being linked to.
				temp = get_address_of_room_by_name(ft_strchr(STR, '-') + 1, obj);
				// if (temp != CCURRENT)
					create_t_link_node(temp, CCURRENT, 1);
				// create t_links node with address returned from
				// get_address_of_room_by_name().
			}
			if (STR_L->next != NULL)
				copy = STR_L;
			STR_L = STR_L->next;
		}
		STR_L = copy;
		CCURRENT = CCURRENT->next;
	}
	return (1);
}

int				check_first_line(t_obj *obj)
{
	int			i;

	i = 0;
	while (STR[i])
	{
		if (!ft_isdigit(STR[i]) && STR[i] != '\n')
		{
			ft_putstr_fd("Error, first line not a digit or has zero ants\n", 0);
			return (0);
		}
		++i;
	}
	ANTS = ft_atoi(STR);
	STR_L = STR_L->next;
	return (1);
}

int				assign_input_to_obj(t_obj *obj)
{
	int			i;

	i = 0;
	if (!check_first_line(obj))
		return (0);
	// continue checking next lines
	while (STR_L && STR_L->next != NULL)
	{
		i = validate_string_list(STR);
		// move to next string if current line is ##start or ##end
		// must check current newline in validate_string_list()
		if (i == 1)
			create_room_node(obj, i);
		else if (i == 2 || i == 3)
		{
			STR_L = STR_L->next;
			if (validate_string_list(STR))
				create_room_node(obj, i);
			else
			{
				// delete_lnkd_list(obj); have to write this
				return (0);
			}
		}
		else if (i == 5)
		{
			populate_beginning_links_to_string_list(STR_L, obj);
			return (1);
		}
		else if (i == 0)
		{
			// delete_lnkd_list(obj);	have to write this
			ft_putstr_fd("Error, not valid map\n", 2);
			return (0);
		}
		STR_L = STR_L->next;
	}
	return (1);
}

void			populate_beginning_links_to_string_list(t_str *beginning_links, t_obj *obj) // make sure all lnkd_lists have members correctly assigned
{
	STR_L = STR_L->beginning;
	// printf("inside populate() var beginning_list:%p, STR:%p\n", beginning_links, STR_L);
	while (STR_L && STR_L->next != NULL)
	{
		STR_L->beginning_links = beginning_links;
		STR_L = STR_L->next;
	}
	STR_L->beginning_links = beginning_links;
	STR_L = STR_L->beginning;
}
/*
	i = validate_string()
	if i == ##start or ##end
	validate_string() for next string inside create_room_node()
*/