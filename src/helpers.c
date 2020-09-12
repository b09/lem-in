/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/26 13:10:28 by bprado        #+#    #+#                 */
/*   Updated: 2020/07/20 13:37:12 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

/*
**	func() will traverse the t_room linked list until it finds
**	the room that matches the name it seeks, will then return that found
**	room's address
*/

t_room			*get_troom_by_name(char *str, t_lemin *lemin)
{
	t_room		*temp;

	temp = lemin->head_rm;
	while (temp)
	{
		if (!ft_memcmp(temp->name, str, ft_strlen(temp->name)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int				assign_level(t_lemin *lemin)
{
	if (lemin->curr_q)
	{
		if (lemin->room->path
			&& lemin->room->path->prnt_rm == lemin->room->links->room)
			return (lemin->curr_q->level - 1);
		else
			return (lemin->curr_q->level + 1);
	}
	return (1);
}

/*
**	called in bfs() while loop
**	will exit bfs() if func() returns 1
**	Returns 1 if the current room links to end room (therefore end found)
**	but not if link between current room and end room has been used before in
**	previous bfs() call which resulted in a valid path.
*/

int				check_endrm(t_lemin *lemin)
{
	if (lemin->room->links->room == lemin->end_room)
	{
		if (lemin->room->path
			&& lemin->room->path->child_room == lemin->end_room)
			return (0);
		return (1);
	}
	return (0);
}

/*
**	called in check_room_add_to_queue() to check whether the child room
*/

int				check_parent_queue(t_lemin *lemin)
{
	t_link		*links;

	links = lemin->room->links->room->head_lnk;
	while (links)
	{
		if (links->room == lemin->room && links->queue)
		{
			return (1);
		}
		links = links->next;
	}
	return (0);
}

void			assign_path(t_lemin *lemin, t_queue *queue)
{
	queue->assign_to_path = 1;
	if (queue && queue->prnt_rm != lemin->start_room)
		assign_path(lemin, queue->parent_queue);
}
