/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lem-in.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/04/10 21:16:09 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN

# define FT_LEMIN

#include "libft.h"

# define ANTS		obj->ants
# define START		obj->start_room
# define STRING		obj->string
# define END		obj->end_room
# define CSTART		obj->chain_start
# define CCURRENT	obj->chain_current
# define CEND		obj->chain_end
# define INPUT_STR	obj->input_string
# define NAME		obj->

typedef	struct		s_room
{
	char			*name;
	char			*string;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
	struct s_room	*previous;
	struct s_room	*connections;
}					t_room;

typedef struct		s_str
{
	char			*str;
	struct s_str	*next;
	struct s_str	*beginning;
}					t_str;

typedef struct		s_obj
{
	int				ants;
	int				room_count;
	t_str			*string;
	// chain_start is an arbitrary start to the linked list
	// but it guarantees to connect every node for easy deletion.
	// the linked list may be created before start_room is
	// identified
	t_room			*chain_start;
	t_room			*chain_end;
	t_room			*chain_current;

	t_room			*start_room;
	t_room			*end_room;
}					t_obj;



#endif
