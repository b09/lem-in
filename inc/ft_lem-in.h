/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lem-in.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/21 16:50:44 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN

# define FT_LEMIN

#include "libft.h"
#include "ft_printf.h"
#include <stdbool.h>

# define ANTS		obj->ants
# define START_RM	obj->start_room
# define END_RM		obj->end_room
# define ROOM		obj->c_room
# define TSTR_L		obj->tstr_current_str
# define TSTR_STRT	obj->tstr_start
# define CSTART		obj->chain_start
# define CEND		obj->chain_end
# define INPUT_STR	obj->input_string
# define LINKS_STRT	obj->beginning_links
# define QCURRENT	obj->q_current
# define QHEAD		obj->q_head
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
	int				ant;
	
	struct s_room	*next;
	struct s_room	*previous;

	struct s_link	*links;
	struct s_link	*start_link;

	// value must be incremented AND decremented whithin same bfs() call.
	bool			parent_went_against_path;
	// int				number_of_times_on_queue;
	
	// bool			on_queue_outgoing;
	// bool			room_on_path;
	bool			dead_end;
	int				level;
	struct s_queue	*queue;
	struct s_queue	*path;

}					t_room;

typedef struct		s_link
{
	t_room			*room;
	bool			on_queue_outgoing;
	struct s_queue	*lnk_queue;
	bool			on_queue_incoming;
	struct s_link	*next;
}					t_link;

typedef struct		s_queue
{
	bool			q_on_path;
	t_room			*parent_room;
	struct s_queue	*parent_queue;
	t_room			*current_room;
	/// child_room, child_queue populated once path found
	t_room			*child_room;
	struct s_queue	*child_queue;

	t_link			*parent_links_child;
	int				level;
	int				path_total_steps;
	int				min_ants;
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
	t_room			*c_room;

	t_room			*start_room;
	t_room			*end_room;

	t_queue			*q_start;
	t_queue			*q_current;
	t_queue			*q_head;
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
int				remove_dead_end_paths(t_obj *obj, t_room *all_rooms, t_room *current_room, t_room *parent, t_room *temp);




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
void			print_heuristic_level(t_obj *obj);
void			connect_everything(t_obj *obj);
void			assign_total_steps_to_paths(t_obj *obj);
void			assign_min_ants_for_use_of_paths(t_obj *obj);
int				get_number_of_paths(t_obj *obj);
void			move_and_print_ants(t_obj *obj);




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
void            create_tqueue_node(t_obj *obj);//, bool negative_level);
void            breadth_first_search(t_obj *obj);
void			assign_path(t_obj *obj, t_queue *room);
void			delete_tqueue_nodes(t_obj *obj, t_queue *queue);
void			connect_tqueue_nodes(t_obj *obj);//, t_room *current_room, t_room *child_room);
int				count_links(t_link *room);
void			print_queue_from_qend(t_obj *obj);
int				check_parent_queue(t_obj *obj);
int				assign_level(t_obj *obj);









/*
**	malloced content:
**		tstr_l
**		tstr_l->str
**		t_room
**		t_room->links
*/

#endif
