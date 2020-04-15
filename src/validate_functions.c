/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 14:24:47 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/15 16:11:54 by macbook       ########   odam.nl         */
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
		if ((!ft_isprint(str[i]) && str[i] != '-' && str[i] != '\n') || \
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


int				validate_first_line(t_obj *obj)
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
	TSTR_L = TSTR_L->next;
	return (1);
}