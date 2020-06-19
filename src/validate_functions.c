/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 14:24:47 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/19 20:21:58 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

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
		if ((!ft_isprint(str[i]) && str[i] != '\n') || \
			(i == 0 && str[i] == '-') || (str[i] == ' '))
			return (0);
		if (str[i] == '-')
			++dash;
		++i;
	}
	if (dash != 1)
		return (0);
	return (5);
}

/*
**	check strings with first character '#'
**	return different ints depeding on whether str is ##start
**	##end or comment beginning with #
*/
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
**	ensure that original input is validated
**	returns:
**		0
**		1 = valid string describing room name with coordinates
**		2 = str describes ##start, ie. start room
**		3 = str describes ##end, ie. end room
**		4 = normal comment, ignore
**		5 = str describes a link
*/
int				validate_string_list(char *str)
{
	int			i;
	int			spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (str[i] != '\n' && (!ft_isprint(str[i]) || (i == 0 && str[i] == ' ')))
		{
			ft_putstr_fd("Error, invalid character in line\n", 2);
			return (0);
		}
		if (str[i] == 'L' && str[i + 1] == ' ')
		{
			ft_putstr_fd("Error, room named >> L << not permitted\n", 2);
			return (0);
		}
		if (str[i] == '#' && i == 0)
			return (validate_comment(str));
		if (str[i] == ' ')
		{
			++spaces;
			++i;
		}
		if (spaces > 0 && !ft_isdigit(str[i]) && str[i] != '\n')
		{
			ft_putstr_fd("Error, coordinate is not a digit\n", 2);
			return (0);
		}
		++i;
	}
	if (spaces != 2)
		return (validate_link(str));
	return (1);
}


int				validate_first_line(t_obj *obj)
{
	int			i;
	int			characters;

	characters = 0;
	i = 0;
	TSTR_L = TSTR_STRT;
	while (STR[i] == '#')
		TSTR_L = TSTR_L->next;
	while (STR[i])
	{
		if (!ft_isdigit(STR[i]) && STR[i] != '\n')
		{
			ft_putstr_fd("Error, first line not a digit or has zero ants\n", 2);
			return (0);
		}
		++characters;
		++i;
	}
	if (characters > 10 || (ft_atol(&STR[i - characters]) > INT32_MAX ||\
	ft_atol(&STR[i - characters]) < INT32_MIN))
		return (0);
	ANTS = ft_atoi(STR);
	TSTR_L = TSTR_L->next;
	return (1);
}

int				check_duplicate_coordinates(t_obj *obj)
{
	t_room 		*temp;
	
	temp = CSTART;
	while (temp)
	{
		ROOM = temp->next;
		while (ROOM && temp)
		{
			if (ROOM->coord_x == temp->coord_x)
			{
				if (ROOM->coord_y == temp->coord_y)
					return (0);
			}
			ROOM = ROOM->next;
		}
		temp = temp->next;
	}
	return (1);
}

int				check_duplicate_rooms_and_coordinates(t_obj *obj)
{
	t_room 		*temp;

	temp = CSTART;
	while (temp)
	{
		ROOM = temp->next;
		while (ROOM && temp)
		{
			if (ft_strcmp(ROOM->name, temp->name) == 0)
				return (0);
			ROOM = ROOM->next;
		}
		temp = temp->next;
	}
	return (check_duplicate_coordinates(obj));
}



/*
**	iterate through all room-links-rooms that are dead_end == 0
**	count links in each room, and if any room has only one link, 
**	continue from room 1 to room 2, check its links, and if only 2
**	links, continue until 3 links are found, or 1 ....
**	ex: dead_end->room2->room1->start->roomA->roomB->end->roomY->roomZ->dead_end
*/



void			remove_dead_ends(t_obj *obj)
{
	t_room 		*room;
	t_room		*dead_end;
	int			link_count;

	room = CSTART;
	while (room)
	{
		if (room->start_link && !room->start_link->next)
		{
			dead_end = room->start_link->room;
			while (count_links(dead_end->start_link) < 3)
			{
				dead_end = dead_end->start_link->room;
			}
		}
		
		room = room->next;
	}
}