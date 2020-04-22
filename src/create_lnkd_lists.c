/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lnkd_lists.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:51:15 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/21 16:21:31 by macbook       ########   odam.nl         */
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
int				create_tstr_lst(t_obj *obj)
{
	char		*str;
	t_str		*temp;

	temp = NULL;
	gnl_with_newline(0, &str);
	if (str)
	{
		TSTR_L = ft_memalloc(sizeof(t_str));
		TSTR_L->str = str;
		TSTR_L->next = NULL;
		TSTR_STRT = TSTR_L;
		while (gnl_with_newline(0, &str) > 0)
		{
			temp = ft_memalloc(sizeof(t_str));
			temp->str = str;
			temp->next = NULL;
			TSTR_L->next = temp;
			TSTR_L = temp;
		}
	}
	TSTR_L = TSTR_STRT;
	return (1);
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
	if (room->start_link == NULL)
	{
		room->start_link = new_node;
		room->links = new_node;
	}
	else
	{
		room->links->next = new_node;
		room->links = new_node;
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
**
**	func() creates t_room node, assigns all members
**	except *links
*/
int				create_troom_node(t_obj *obj, int code)
{
	int			i;

	i = 0;
	CCURRENT = ft_memalloc(sizeof(t_room));
	while (STR[i] && STR[i] != ' ')
		++i;
	CCURRENT->name = ft_strndup(STR, i);
	CCURRENT->coord_x = ft_atoi(&STR[i + 1]);// for space in string
	while (STR[i + 1] && ft_isdigit(STR[i + 1]))
		++i;
	CCURRENT->coord_y = ft_atoi(&STR[i + 2]); // for second space
	if (CSTART == NULL)
		CSTART = CCURRENT;
	else
	{
		CEND->next = CCURRENT;
		CCURRENT->previous = CEND;
	}
	if (code == 2)
		START_RM = CCURRENT;
	else if (code == 3)
		END_RM = CCURRENT;
	CEND = CCURRENT;
	return (1);
}

/*
**	func() will traverse the t_room linked list until it finds
**	the room that matches the name it seeks, will then return that found
**	room's address
*/
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
**	func() will create a t_link linked list for every room
**	by checking every line in the t_str linked list starting
**	at the string where the link descriptions begin.
**	while there are rooms, if a string (starting at the string
**	that describes links) contains the name of the current room,
**	make a t_link node for room1 to room2 and for room2 to room1
**	
*/
int				create_tlink_lst(t_obj *obj)
{
	t_room 		*temp;
	t_room 		*temp2;
	
	TSTR_L = BEGIN_LNKS;
	while (TSTR_L && TSTR_L->next != NULL && validate_link(STR))
		TSTR_L = TSTR_L->next;
	if (TSTR_L->next != NULL && !validate_link(STR))
		return (0);
	TSTR_L = BEGIN_LNKS;
	while (TSTR_L != NULL)
	{
		if (STR[0] != '#')
		{
			temp = get_troom_by_name(STR, obj);
			temp2 = get_troom_by_name(ft_strchr(STR, '-') + 1, obj);
			create_tlink_node(temp, temp2, 1);
		}
		TSTR_L = TSTR_L->next;
	}
	return (1);
}

/*
**	func() navigates the t_str linked list, which in every node contains
**	a string from the stdin. Every string is validated until it reaches a
**	string which does not describe a room with coordinates in the format
**	"(char*)roomname (int)coord-x (int)coord-y". For every valid string
**	a t_room node is created.
*/
int				create_troom_lst(t_obj *obj)
{
	int			i;

	if (!validate_first_line(obj))
		return (0);
	i = 0;
	while (TSTR_L && TSTR_L->next != NULL)
	{
		i = validate_string_list(STR);
		if (i == 1)
			create_troom_node(obj, i);
		else if (i == 2 || i == 3)
		{
			TSTR_L = TSTR_L->next;
			if (validate_string_list(STR))
				create_troom_node(obj, i);
			else
				return (0);
		}
		else if (i == 5)
		{
			BEGIN_LNKS = TSTR_L;
			return (1);
		}
		else if (i == 0)
			return (0);
		TSTR_L = TSTR_L->next;
	}
	return (1);
}