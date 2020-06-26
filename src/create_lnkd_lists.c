/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lnkd_lists.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:51:15 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/26 16:57:15 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
**	strutct t_str members:
**		char			*str;
**		struct s_str	*next;
**
**	get input from stdin with gnl_with_newline()
**	malloc a t_str node and assign gnl() output to node->str,
**	connect nodes
**	func() will make a copy of the input (the map) from which a linked list
**	rooms and a linked list of links is created later on. The copy of the input
**	will be printed to the screen if validation checks are passed.
*/

int				create_tstr_lst(t_obj *obj)
{
	char		*str;
	t_str		*temp;

	temp = NULL;
	gnl_with_newline(0, &str);
	if (str)
	{
		obj->tstr = ft_memalloc(sizeof(t_str));
		obj->tstr->str = str;
		obj->tstr->next = NULL;
		obj->head_tstr = obj->tstr;
		while (gnl_with_newline(0, &str) > 0)
		{
			temp = ft_memalloc(sizeof(t_str));
			temp->str = str;
			temp->next = NULL;
			obj->tstr->next = temp;
			obj->tstr = temp;
		}
		obj->tstr = obj->head_tstr;
		return (1);
	}
	return (print_error(NO_INPUT));
}

/*
**	strutct t_link members:
**		t_room			*room;
**		struct s_queue	*queue;
**		struct s_link	*next;
**
**	initial input to executable (./lemin) will be a map containing:
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

void			create_tlink_node(t_room *linked_rm, t_room *room, char repeat)
{
	t_link		*t_links;

	if (linked_rm == room)
		return ;
	t_links = ft_memalloc(sizeof(t_link));
	t_links->room = linked_rm;
	t_links->next = NULL;
	if (room->head_lnk == NULL)
	{
		room->head_lnk = t_links;
		room->links = t_links;
	}
	else
	{
		room->links->next = t_links;
		room->links = t_links;
	}
	if (repeat)
		create_tlink_node(room, linked_rm, 0);
}

/*
**	struct		s_room
**
**		char			*name;
**		int				coord_x;
**		int				coord_y;
**		int				ant;
**		struct s_room	*next;
**		struct s_room	*previous;
**		struct s_link	*links;
**		struct s_link	*head_lnk;
**		bool			dead_end;
**		int				level;
**		struct s_queue	*queue;
**		struct s_queue	*path;
**
**	func() creates t_room node, assigns some members, remainig members assigned
**	later
*/

int				create_troom_node(t_obj *obj, int code)
{
	int			i;

	i = 0;
	obj->room = ft_memalloc(sizeof(t_room));
	while (obj->tstr->str[i] && obj->tstr->str[i] != ' ')
		++i;
	obj->room->name = ft_strndup(obj->tstr->str, i);
	obj->room->coord_x = ft_atoi(&obj->tstr->str[i + 1]);
	while (obj->tstr->str[i + 1] && ft_isdigit(obj->tstr->str[i + 1]))
		++i;
	obj->room->coord_y = ft_atoi(&obj->tstr->str[i + 2]);
	if (obj->head_rm == NULL)
		obj->head_rm = obj->room;
	else
	{
		obj->tail_rm->next = obj->room;
		obj->room->prev = obj->tail_rm;
	}
	if (code == 2)
		obj->start_room = obj->room;
	else if (code == 3)
		obj->end_room = obj->room;
	obj->tail_rm = obj->room;
	return (1);
}

/*
**	func() will create a t_link linked list for every room
**	by checking every line in the t_str linked list starting
**	at the string where the link descriptions begin.
**	while there are rooms, if a string (starting at the string
**	that describes links) contains the name of the current room,
**	make a t_link node for room1 to room2 and for room2 to room1
*/

int				create_tlink_lst(t_obj *obj)
{
	t_room		*temp;
	t_room		*temp2;

	obj->tstr = obj->head_lnk_str;
	while (obj->tstr != NULL && validate_link(obj->tstr->str))
		obj->tstr = obj->tstr->next;
	if (obj->tstr != NULL && !validate_link(obj->tstr->str))
		return (print_error(BAD_LINK));
	obj->tstr = obj->head_lnk_str;
	while (obj->tstr != NULL)
	{
		if (obj->tstr->str[0] != '#')
		{
			temp = get_troom_by_name(obj->tstr->str, obj);
			temp2 = get_troom_by_name(ft_strchr(obj->tstr->str, '-') + 1, obj);
			if (!temp || !temp2 || temp == temp2)
				return (print_error(NO_RM_LINK));
			create_tlink_node(temp, temp2, 1);
		}
		obj->tstr = obj->tstr->next;
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
	int			val_str_code;

	validate_first_line(obj);
	val_str_code = 0;
	while (obj->tstr && obj->tstr->next != NULL)
	{
		val_str_code = validate_string_list(obj->tstr->str);
		if (val_str_code == 1)
			create_troom_node(obj, val_str_code);
		else if (val_str_code == 2 || val_str_code == 3)
		{
			obj->tstr = obj->tstr->next;
			validate_string_list(obj->tstr->str);
			create_troom_node(obj, val_str_code);
		}
		else if (val_str_code == 5)
		{
			obj->head_lnk_str = obj->tstr;
			return (1);
		}
		obj->tstr = obj->tstr->next;
	}
	return (1);
}
