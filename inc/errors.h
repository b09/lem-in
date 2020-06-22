/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 12:30:38 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/22 13:57:22 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEMIN_ERRORS

# define LEMIN_ERRORS

# define NOT_DIGIT		"Error, first line not a digit\n"
# define ZERO_ANTS		"Error, zero ants or number is to large\n"
# define BAD_CHAR		"Error, invalid character in line\n"
# define BAD_L			"Error, room named >> L << not permitted\n"
# define BAD_COOR		"Error, coordinate is not a digit\n"
# define BAD_LINK		"Error, not a valid link\n"
# define DUP_NAME		"Error, there are two rooms with the same name\n"
# define DUP_COOR		"Error, there are two rooms with the same coordinates\n"
# define NO_INPUT		"Error, no input\n"
# define NO_RM_LINK		"Error, link describe a nonexistent room\n"

#endif