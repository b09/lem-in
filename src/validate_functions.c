/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 14:24:47 by macbook       #+#    #+#                 */
/*   Updated: 2020/07/20 13:36:51 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

/*
**	iterate thru string list starting from string that
**	is not a string describing rooms, just links
*/

int				validate_link(char *str)
{
	int			i;
	int			dash;

	i = 0;
	dash = 0;
	while (str[i])
	{
		if (str[0] == '#')
			break ;
		if ((str[i] == ' ')
			|| (!ft_isprint(str[i]) && str[i] != '\n')
			|| (i == 0 && (str[i] == '\n' || str[i] == '-')))
			return (0);
		if (str[i] == '-')
			++dash;
		++i;
	}
	if (dash != 1 && str[0] != '#')
		return (0);
	return (5);
}

/*
**	check strings with first character '#'
**	return different ints depeding on whether str is ##start
**	##end or comment beginning with #
*/

int				validate_comment(char *str, t_lemin *lemin)
{
	if (ft_strcmp(str, "##start\n") == 0)
	{
		lemin->flags |= START_CMMT;
		return (2);
	}
	else if (ft_strcmp(str, "##end\n") == 0)
	{
		lemin->flags |= END_CMMT;
		return (3);
	}
	else
		return (4);
}

/*
**	ensure that original input is validated
**	returns:
**		0
**		1 = valid string describing room name with coordinates
**		2 = str describes ##start, ie. start room
**		3 = str describes ##end, ie. end room
**		4 = normal comment, ignore
**		5 = str describes a link
*/

int				validate_string_list(char *str, t_lemin *lemin)
{
	int			i;
	int			spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (str[i] != '\n' && (!ft_isprint(str[i]) || (!i && str[i] == ' ')))
			return (print_error(BAD_CHAR));
		if (str[0] == 'L' && str[1] && str[1] == ' ')
			return (print_error(BAD_L));
		if (str[i] == '#' && i == 0)
			return (validate_comment(str, lemin));
		spaces += str[i] == ' ' ? 1 : 0;
		i += str[i] == ' ' ? 1 : 0;
		if (spaces > 0 && !ft_isdigit(str[i]) && str[i] != '\n')
			return (print_error(BAD_COOR));
		++i;
		if (spaces && ft_numlen(&str[i]) > 10)
			return (print_error(LRG_COOR));
	}
	if (spaces != 2)
		return (validate_link(str));
	return (1);
}

/*
**	replace below line in fuction if running on linux
**	if (chars > 10 || (ft_atol(&lemin->tstr->str[i - chars]) > INT_MAX
** 			|| ft_atol(&lemin->tstr->str[i - chars]) < INT_MIN)
**		|| ft_atol(lemin->tstr->str) == 0)
**	// for valgrind on docker
*/

int				validate_first_line(t_lemin *lemin)
{
	int			i;
	int			chars;

	chars = 0;
	i = 0;
	lemin->tstr = lemin->head_tstr;
	while (lemin->tstr->str[i] == '#')
		lemin->tstr = lemin->tstr->next;
	while (lemin->tstr->str[i])
	{
		if (!ft_isdigit(lemin->tstr->str[i]) && lemin->tstr->str[i] != '\n')
			return (print_error(NOT_DIGIT));
		++chars;
		++i;
	}
	if (chars > 10
		|| (ft_atol(&lemin->tstr->str[i - chars]) > INT32_MAX
			|| ft_atol(&lemin->tstr->str[i - chars]) < INT32_MIN)
		|| ft_atol(lemin->tstr->str) == 0)
		return (print_error(ZERO_ANTS));
	lemin->ants = ft_atoi(lemin->tstr->str);
	lemin->tstr = lemin->tstr->next;
	return (1);
}

/*
**	iterate through all room-links-rooms that are dead_end == 0
**	count links in each room, and if any room has only one link,
**	continue from room 1 to room 2, check its links, and if only 2
**	links, continue until 3 links are found, or 1 ....
**	ex: dead_end->room2->room1->start->roomA->roomB->end->roomY->roomZ->dead_end
*/

int				remove_dead_end_paths
	(t_lemin *lemin, t_room *all_rooms, t_room *cur_room, t_room *parent)
{
	t_room		*temp;

	temp = NULL;
	while (all_rooms != lemin->head_rm)
	{
		if (all_rooms->head_lnk && !all_rooms->head_lnk->next
			&& all_rooms != lemin->end_room && all_rooms != lemin->start_room)
		{
			cur_room = all_rooms->head_lnk->room;
			parent = all_rooms;
			while (cur_room != lemin->start_room && cur_room != lemin->end_room
					&& count_links(cur_room->head_lnk) == 2)
			{
				temp = cur_room;
				cur_room = cur_room->head_lnk->room == parent ?\
				cur_room->head_lnk->next->room : cur_room->head_lnk->room;
				parent = temp;
			}
			if (cur_room == lemin->start_room || cur_room == lemin->end_room
				|| count_links(cur_room->head_lnk) > 2)
				parent->dead_end = 1;
		}
		all_rooms = all_rooms->next;
	}
	return (1);
}
