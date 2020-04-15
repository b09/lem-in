/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lem-in.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/04/15 18:37:32 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN

# define FT_LEMIN

#include "libft.h"

# define ANTS		obj->ants
# define START_RM	obj->start_room
# define TSTR_L		obj->tstr_list
# define END_RM		obj->end_room
# define CSTART		obj->chain_start
# define CCURRENT	obj->chain_current
# define CEND		obj->chain_end
# define INPUT_STR	obj->input_string
# define BEGIN_LNKS	obj->beginning_links
// # define NAME		obj->
# define STR		TSTR_L->str

/*
**	name of room
**	coord_x of room	
**	coord_y of room
**	addr of next room	
**	addr of previous room
**	lnk list of rooms that node connects to
**	addr of start room as described by "##start"	
*/
typedef	struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	struct s_room	*next;
	struct s_room	*previous;
	struct s_link	*links;
	struct s_room	**start_room;
}					t_room;

typedef struct		s_link
{
	t_room			*room;
	struct s_link	*start;
	struct s_link	*current;
	struct s_link	*next;
}					t_link;

typedef struct		s_str
{
	char			*str;
	struct s_str	*next;
	struct s_str	*beginning;
	struct s_str	**beginning_links;
}					t_str;

typedef struct		s_obj
{
	int				ants;
	int				room_count;
	t_str			*tstr_list;
	t_str			*beginning_links;
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

/*
**	validate_functions.c
*/
int				validate_link(char *str);
int				validate_comment(char *str);
int				validate_string_list(char *str);
int				validate_first_line(t_obj *obj);

/*
**	print_functions.c
*/
void			delete_string_lst(t_obj *obj, t_str **list);
void			print_tstr_lst(t_obj *obj);
void			print_troom_lst(t_obj *obj);
void			print_tlink_lst(t_obj *obj);

/*
**	lem-in.c
*/
void			populate_beginning_links_to_string_list(t_str *beginning_links, t_obj *obj); // make sure all lnkd_lists have members correctly assigned

/*
**	create_lnkd_lists.c
*/
void			create_tstr_lst(t_obj *obj);
void			create_tlink_node(t_room *link, t_room *room, char repeat);
int				create_troom_node(t_obj *obj, int code);
t_room			*get_troom_by_name(char *str, t_obj *obj);
int				create_tlink_lst(t_obj *obj);
int				create_troom_lst(t_obj *obj);


#endif
