/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lem_in.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/28 17:32:23 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H

# define FT_LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include "errors.h"
# include <stdbool.h>

# define C_RED		"\x1b[31m"
# define C_GREEN	"\x1b[32m"
# define C_YELLOW	"\x1b[33m"
# define C_BLUE		"\x1b[34m"
# define C_MAGENTA	"\x1b[35m"
# define C_CYAN		"\x1b[36m"
# define C_RESET	"\x1b[0m"

# define START_CMMT	1
# define END_CMMT	2

/*
**		----- struct t_room -----
**	name 		=> name of room
**	coord_x		=> coord_x of room
**	coord_y		=> coord_y of room
**	ant			=> number of ant stored in room
**	next		=> addr of next room
**	prev		=> addr of previous room
**	links		=> temp variable used on program
**	head_lnk	=> head of linked list of rooms that link to (this) current room
**	dead_end	=> flag to identify if room starts path to a deadend
**	level		=> number of steps from current room to start room
**	queue		=> pointer to queue node in which current room was added
**	path		=> pointer to queue node which is on a path
**	addr of start room as described by "##start"
*/

typedef	struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				ant;
	struct s_room	*next;
	struct s_room	*prev;
	struct s_link	*links;
	struct s_link	*head_lnk;
	bool			dead_end;
	int				level;
	struct s_queue	*queue;
	struct s_queue	*path;
}					t_room;

/*
**		----- struct t_link -----
**	room		=> pointer to child room that parent room links to
**	queue		=> pointer to t_queue node by which parent room added child \
**			<= room to the queue
**	next		=> pointer to next t_link, containing the child room which \
**			<= parent rooms links to
*/
typedef struct		s_link
{
	t_room			*room;
	struct s_queue	*queue;
	struct s_link	*next;
}					t_link;

/*
**		----- struct t_queue -----
**	assign_to_path=> flag specifying current t_queue node is part of a path
**	prnt_rm		=> pointer to parent room which added room to the queue
**	parent_queue=> pointer to t_queue node in which the parent room is room
**	room		=> pointer to the current room
**	child_room	=> populated once path is found, points to next room in path
**	level		=> number of steps from which room distanced to start room
**	path_len	=> len of path, only assigned on node for room at start of path
**	min_ants	=> min number of ants which must be in strtrm to use path
**	next		=> next queue node, used for printing and deleting funcs()
*/
typedef struct		s_queue
{
	bool			assign_to_path;
	t_room			*prnt_rm;
	struct s_queue	*parent_queue;
	t_room			*room;
	t_room			*child_room;
	int				level;
	int				path_len;
	int				min_ants;
	struct s_queue	*next;
}					t_queue;

/*
**		----- struct t_str -----
**	str			=> content copied from stdin up to and including newline
**	next		=> pointer to next t_str containing next str
*/
typedef struct		s_str
{
	char			*str;
	struct s_str	*next;
}					t_str;

/*
**		----- strtuct t_obj -----
**	ants		=> number of ants in start room
**	room_count	=> number of rooms on map
**	flags		=> ensures ##start and ##end are active
**	tstr		=> temp variable for a t_str node
**	head_tstr	=> pointer to the start of t_str linked list
**	head_lnk_str=> pointer to start of t_str describing links
**	head_rm		=> pointer to start of t_room linked list
**	tail_rm		=> pointer to end of t_room linked list
**	room		=> temp variable for holding a t_room node
**	start_room	=> pointer to room which is the start room on the map
**	end_room	=> pointer to room which is the end room on the map
**	head_q		=> pointer to head of t_queue linked list
**	temp_q		=> temp variable for used for t_queue nodes
**	curr_q		=> pointer for t_queue currently being evaluated
**	tail_q		=> pointer to end of the t_queue linked list
*/
typedef struct		s_obj
{
	int				ants;
	int				room_count;
	char			flags;
	t_str			*tstr;
	t_str			*head_tstr;
	t_str			*head_lnk_str;
	t_room			*head_rm;
	t_room			*tail_rm;
	t_room			*room;
	t_room			*start_room;
	t_room			*end_room;
	t_queue			*head_q;
	t_queue			*temp_q;
	t_queue			*curr_q;
	t_queue			*tail_q;
}					t_obj;

/*
**	validate_functions.c
*/

int					validate_link(char *str);
int					validate_comment(char *str, t_obj *obj);
int					validate_string_list(char *str, t_obj *obj);
int					validate_first_line(t_obj *obj);
int					check_duplicate_rooms_and_coordinates(t_obj *obj);
int					check_duplicate_coordinates(t_obj *obj);
int					remove_dead_end_paths(t_obj *obj, t_room *all_rooms, t_room\
			*current_room, t_room *parent);
int					print_error(char *str);

/*
**	delete_functions.c
*/

void				delete_string_lst(t_str **list);
void				delete_troom_lst(t_room **list);
void				delete_tlink_lst(t_link **list);
void				delete_all(t_obj *obj);

/*
**	print_functions.c
*/

void				print_tstr_lst(t_obj *obj);
void				print_troom_lst(t_obj *obj);
void				print_tlink_lst(t_obj *obj);
void				print_tqueue_lst(t_obj *obj);
void				print_tqueue_path(t_obj *obj, t_room *temp);
void				print_multiple_paths(t_obj *obj, t_room *room, t_link\
			*links_startroom);

/*
**	lem-in.c
*/

int					init_lists_and_print(t_obj *obj);
void				print_heuristic_level(t_obj *obj);
void				connect_everything(t_obj *obj, double steps, double steps2,\
			int paths);
void				assign_total_steps_to_paths(t_obj *obj);
void				assign_min_ants_for_use_of_paths(t_obj *obj, int steps,\
			int ants, int ant_counter);
int					get_number_of_paths(t_obj *obj);
void				move_and_print_ants(t_obj *obj, int current_ant,\
			int end_rm_ants, int ants_copy);

/*
**	create_lnkd_lists.c
*/

int					create_tstr_lst(t_obj *obj);
void				create_tlink_node(t_room *link, t_room *room, char repeat);
int					create_troom_node(t_obj *obj, int code);
t_room				*get_troom_by_name(char *str, t_obj *obj);
int					create_tlink_lst(t_obj *obj);
int					create_troom_lst(t_obj *obj);

/*
**	solver.c
*/

void				create_tqueue_node(t_obj *obj);
void				breadth_first_search(t_obj *obj, int paths);
void				assign_path(t_obj *obj, t_queue *room);
void				delete_tqueue_nodes(t_obj *obj, t_queue *queue);
void				connect_tqueue_nodes(t_obj *obj);
int					count_links(t_link *room);
void				print_queue_from_qend(t_obj *obj);
int					check_parent_queue(t_obj *obj);
int					assign_level(t_obj *obj);

/*
**	helpers.c
*/

int					check_endrm(t_obj *obj);

/*
**	malloced content:
**		tstr_l
**		tstr_l->str
**		t_room
**		t_room->links
*/

#endif
