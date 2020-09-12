/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lnkd_lists.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:51:15 by macbook       #+#    #+#                 */
/*   Updated: 2020/07/02 19:25:22 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

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

int				create_tstr_lst(t_lemin *lemin, int fd)
{
	char		*str;
	t_str		*temp;

	temp = NULL;
	gnl_with_newline(fd, &str);
	if (str)
	{
		lemin->tstr = ft_memalloc(sizeof(t_str));
		lemin->tstr->str = str;
		lemin->tstr->next = NULL;
		lemin->head_tstr = lemin->tstr;
		while (gnl_with_newline(fd, &str) > 0)
		{
			temp = ft_memalloc(sizeof(t_str));
			temp->str = str;
			temp->next = NULL;
			lemin->tstr->next = temp;
			lemin->tstr = temp;
		}
		lemin->tstr = lemin->head_tstr;
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

int				create_troom_node(t_lemin *lemin, int code)
{
	int			i;

	i = 0;
	lemin->room = ft_memalloc(sizeof(t_room));
	while (lemin->tstr->str[i] && lemin->tstr->str[i] != ' ')
		++i;
	lemin->room->name = ft_strndup(lemin->tstr->str, i);
	lemin->room->coord_x = ft_atoi(&lemin->tstr->str[i + 1]);
	while (lemin->tstr->str[i + 1] && ft_isdigit(lemin->tstr->str[i + 1]))
		++i;
	lemin->room->coord_y = ft_atoi(&lemin->tstr->str[i + 2]);
	if (lemin->head_rm == NULL)
		lemin->head_rm = lemin->room;
	else
	{
		lemin->tail_rm->next = lemin->room;
		lemin->room->prev = lemin->tail_rm;
	}
	if (code == 2)
		lemin->start_room = lemin->room;
	else if (code == 3)
		lemin->end_room = lemin->room;
	lemin->tail_rm = lemin->room;
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

int				create_tlink_lst(t_lemin *lemin)
{
	t_room		*t1;
	t_room		*t2;

	if (lemin->flags != 3 || !lemin->head_lnk_str)
		lemin->flags != 3 ? print_error(NO_CMMND) : print_error(NO_LINK);
	lemin->tstr = lemin->head_lnk_str;
	while (lemin->tstr != NULL && validate_link(lemin->tstr->str))
		lemin->tstr = lemin->tstr->next;
	if (lemin->tstr != NULL && !validate_link(lemin->tstr->str))
		return (print_error(BAD_LINK));
	lemin->tstr = lemin->head_lnk_str;
	while (lemin->tstr != NULL)
	{
		if (lemin->tstr->str[0] != '#')
		{
			t1 = get_troom_by_name(lemin->tstr->str, lemin);
			t2 = get_troom_by_name(ft_strchr(lemin->tstr->str, '-') + 1, lemin);
			if (!t1 || !t2 || t1 == t2)
				return (print_error(NO_RM_LINK));
			create_tlink_node(t1, t2, 1);
		}
		lemin->tstr = lemin->tstr->next;
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

int				create_troom_lst(t_lemin *lemin)
{
	int			val_str_code;

	validate_first_line(lemin);
	while (lemin->tstr && lemin->tstr->next != NULL)
	{
		val_str_code = validate_string_list(lemin->tstr->str, lemin);
		if (val_str_code == 1)
			create_troom_node(lemin, val_str_code);
		else if (val_str_code == 2 || val_str_code == 3)
		{
			lemin->tstr = lemin->tstr->next;
			validate_string_list(lemin->tstr->str, lemin) == 1
				? create_troom_node(lemin, val_str_code)
				: print_error(BAD_CMMND);
		}
		else if (val_str_code == 5)
		{
			lemin->head_lnk_str = lemin->tstr;
			return (1);
		}
		lemin->tstr = lemin->tstr->next;
	}
	return (1);
}
