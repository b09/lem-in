/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lem-in.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/04/13 22:24:03 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN

# define FT_LEMIN

#include "libft.h"

# define ANTS		obj->ants
# define START_RM	obj->start_room
# define STR_L		obj->string_list
# define END_RM		obj->end_room
# define CSTART		obj->chain_start
# define CCURRENT	obj->chain_current
# define CEND		obj->chain_end
# define INPUT_STR	obj->input_string
# define NAME		obj->
# define STR		STR_L->str

typedef	struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
	struct s_room	*previous;
	struct s_links	*links;
	struct s_room	*start_room;
}					t_room;

typedef struct		s_links
{
	t_room			*room;
	struct s_links	*start;
	struct s_links	*current;
	struct s_links	*next;
}					t_links;

typedef struct		s_str
{
	char			*str;
	struct s_str	*next;
	struct s_str	*beginning;
	struct s_str	*beginning_links;
}					t_str;

typedef struct		s_obj
{
	int				ants;
	int				room_count;
	t_str			*string_list;
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

t_room			*get_address_of_room_by_name(char *str, t_obj *obj);
void			create_t_link_node(t_room *link, t_room *room);
int				assign_links_to_rooms(t_obj *obj);
int				validate_link(char *str);
int				validate_rooms_from_string(t_obj *obj);
int				validate_comment(char *str);
int				validate_string_list(char *str);
int				create_room_node(t_obj *obj, int code);
int				assign_input_to_obj(t_obj *obj);
void			delete_string_list(t_obj *obj, t_str **list);
void			copy_string_input(t_obj *obj);
void			print_string_input(t_obj *obj);
void			print_links(t_obj *obj);


#endif
