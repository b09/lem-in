/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lem-in.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/05/11 17:13:41 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN

# define FT_LEMIN

#include "libft.h"
#include <stdbool.h>

# define ANTS		obj->ants
# define START_RM	obj->start_room
# define END_RM		obj->end_room
# define ROOM		obj->chain_current
# define TSTR_L		obj->tstr_current_str
# define TSTR_STRT	obj->tstr_start
# define CSTART		obj->chain_start
# define CEND		obj->chain_end
# define INPUT_STR	obj->input_string
# define LINKS_STRT	obj->beginning_links
# define QCURRENT	obj->q_current
# define QSTART		obj->q_start
# define QEND		obj->q_end
// # define NAME		obj->chain_current->name
# define STR		obj->tstr_current_str->str

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define C_RESET   "\x1b[0m"

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
	struct s_link	*start_link;
	
	bool			on_queue;
	bool			on_path;
	int				level;
	struct s_queue	*queue;
	struct s_queue	*path;

}					t_room;

typedef struct		s_link
{
	t_room			*room;
	bool			on_queue;
	struct s_link	*next;
}					t_link;

typedef struct		s_queue
{
	t_room			*parent_room;
	t_room			*current_room;
	t_room			*next_room;
	struct s_queue	*next_queue;
	struct s_queue	*prev_queue;
}					t_queue;

typedef struct		s_str
{
	char			*str;
	struct s_str	*next;
}					t_str;

typedef struct		s_obj
{
	int				ants;
	int				room_count;
	
	t_str			*tstr_current_str;
	t_str			*tstr_start;
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

	t_queue			*q_start;
	t_queue			*q_current;
	t_queue			*q_end;
}					t_obj;

/*
**	validate_functions.c
*/
int				validate_link(char *str);
int				validate_comment(char *str);
int				validate_string_list(char *str);
int				validate_first_line(t_obj *obj);
int				check_duplicate_rooms_and_coordinates(t_obj *obj);
int				check_duplicate_coordinates(t_obj *obj);



/*
**	delete_functions.c
*/
void			delete_string_lst(t_str **list);
void			delete_troom_lst(t_room **list);
void			delete_tlink_lst(t_link **list);
void			delete_all(t_obj *obj);

/*
**	print_functions.c
*/
void			print_tstr_lst(t_obj *obj);
void			print_troom_lst(t_obj *obj);
void			print_tlink_lst(t_obj *obj);
void			print_tqueue_lst(t_obj *obj);
void			print_tqueue_path(t_obj *obj, t_room *temp);
void			print_multiple_paths(t_obj *obj);




/*
**	lem-in.c
*/
int				init_lists_and_print(t_obj *obj);


/*
**	create_lnkd_lists.c
*/
int				create_tstr_lst(t_obj *obj);
void			create_tlink_node(t_room *link, t_room *room, char repeat);
int				create_troom_node(t_obj *obj, int code);
t_room			*get_troom_by_name(char *str, t_obj *obj);
int				create_tlink_lst(t_obj *obj);
int				create_troom_lst(t_obj *obj);

/*
**	solver.c
*/
void            create_tqueue_node(t_obj *obj);
void            breadth_first_search(t_obj *obj);
void			assign_path(t_obj *obj, t_room *room);
void			delete_tqueue_nodes(t_obj *obj, t_room *room);
void			connect_tqueue_nodes(t_obj *obj, t_room *current_room, t_room *next_room);
int				solver(t_obj *obj);
int				count_links(t_link *room);






/*
**	malloced content:
**		tstr_l
**		tstr_l->str
**		t_room
**		t_room->links
*/

#endif
