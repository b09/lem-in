/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lnkd_lists.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:51:15 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/15 18:43:37 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**	strutct t_str members:
**		char			*str;
**		struct s_str	*next;
**		struct s_str	*beginning;
**		struct s_str	*beginning_links;
**
**	get input from stdin with gnl_with_newline()
**	malloc a t_str node and assign gnl() output to node->str
**	connect nodes
*/
void			create_tstr_lst(t_obj *obj)
{
	char		*str;
	t_str		*temp;

	temp = NULL;
	gnl_with_newline(0, &str);
	if (str)
	{
		TSTR_L = ft_memalloc(sizeof(t_str));
		TSTR_L->str = str;
		TSTR_L->beginning = TSTR_L;
		TSTR_L->next = NULL;
		TSTR_L->beginning_links = &BEGIN_LNKS;
		while (gnl_with_newline(0, &str) > 0)
		{
			temp = ft_memalloc(sizeof(t_str));
			temp->str = str;
			temp->beginning = TSTR_L->beginning;
			temp->next = NULL;
			TSTR_L->next = temp;
			TSTR_L = temp;
		}
		TSTR_L = TSTR_L->beginning;
	}
}

/*
**	strutct t_link members:
**		t_room			*room;
**		struct s_link	*start;
**		struct s_link	*current;
**		struct s_link	*next;
**	
**	initial input to executable (./lemin) will be:
**		number_of_ants
**		the_rooms
**		the_links
**
**	the_links will be a string in the form "room1-room2"
**	every t_room node contains a t_link list 
**	which is a list of rooms that said room connects to.
**	func() will create a t_link node, assign the address
**  of "room2" which "room1" connects to, and assign
**	itself to the list of t_links of "room1".
**	func() calls itself because if "room1-room2" then
**	room1 needs a link to room2 and vice versa
*/
void			create_tlink_node(t_room *link, t_room *room, char repeat)
{
	t_link		*new_node;

	if (link == room)
		return ;
	new_node = ft_memalloc(sizeof(t_link));
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
		new_node->start = room->links->current->start;
		room->links->current->next = new_node;
		room->links->current = new_node;
	}
	if (repeat)
		create_tlink_node(room, link, 0);
}


/*
**	struct		s_room
**	
**		char			*name;
**		int				coord_x;
**		int				coord_y;
**		struct s_room	*next;
**		struct s_room	*previous;
**		struct s_link	*links;
**		struct s_room	*start_room;
**
**	func() creates t_room node, assigns all members
**	except *start_room and *links
*/
int				create_troom_node(t_obj *obj, int code)
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
	temp->start_room = &START_RM;
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



t_room			*get_troom_by_name(char *str, t_obj *obj)
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
/*
**	assign_input_to_obj() will have called a function 
**	
*/
// int				create_tlink_list(t_obj *obj)
int				create_tlink_lst(t_obj *obj)
{
	t_str 		*copy;
	t_room 		*temp;
	
	// TSTR_L = TSTR_L->beginning_links;
	TSTR_L = BEGIN_LNKS;
	while (TSTR_L && TSTR_L->next != NULL && validate_link(STR))
		TSTR_L = TSTR_L->next;
	if (TSTR_L->next != NULL && !validate_link(STR))
		return (0);
	CCURRENT = CSTART;
	while (CCURRENT != NULL)
	{
		// TSTR_L = *(TSTR_L->beginning_links);
		TSTR_L = BEGIN_LNKS;
		while (TSTR_L)
		{
			if (ft_strnstr(STR, CCURRENT->name, ft_strlen(STR)))
			{
				// go one char beyond '-' in STR to get name of
				// room being linked to.
				temp = get_troom_by_name(ft_strchr(STR, '-') + 1, obj);
					create_tlink_node(temp, CCURRENT, 1);
				// create t_links node with address returned from
				// get_address_of_room_by_name().
			}
			if (TSTR_L->next != NULL)
				copy = TSTR_L;
			TSTR_L = TSTR_L->next;
		}
		TSTR_L = copy;
		CCURRENT = CCURRENT->next;
	}
	return (1);
}


int				create_troom_lst(t_obj *obj)
{
	int			i;

	i = 0;
	if (!validate_first_line(obj))
		return (0);
	// continue checking next lines
	while (TSTR_L && TSTR_L->next != NULL)
	{
		i = validate_string_list(STR);
		// move to next string if current line is ##start or ##end
		// must check current newline in validate_string_list()
		if (i == 1)
			create_troom_node(obj, i);
		else if (i == 2 || i == 3)
		{
			TSTR_L = TSTR_L->next;
			if (validate_string_list(STR))
				create_troom_node(obj, i);
			else
			{
				// delete_lnkd_list(obj); have to write this
				return (0);
			}
		}
		else if (i == 5)
		{
			BEGIN_LNKS = TSTR_L;
			// populate_beginning_links_to_string_list(TSTR_L, obj);
			return (1);
		}
		else if (i == 0)
		{
			// delete_lnkd_list(obj);	have to write this
			ft_putstr_fd("Error, not valid map\n", 2);
			return (0);
		}
		TSTR_L = TSTR_L->next;
	}
	return (1);
}