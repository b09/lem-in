/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 12:50:09 by macbook       #+#    #+#                 */
/*   Updated: 2020/04/10 23:47:27 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

/*
main
	copy_string_input
	print_string_input
	delete_string_input



	get_input
		validate_string
			validate_links
		create_lnkd_list
*/
int				validate_links(char *str);
int				validate_string_list(char *str);
int				create_lnkd_list(char *str, t_obj *obj);
int				get_input(t_obj *obj);
void			copy_string_input(t_obj *obj);
void			print_string_input(t_obj *obj);
void			delete_string_list(t_obj *obj, t_str **list);


int				main(void)
{
    // get content from stdin with gnl
	// first line: number of ants
	// when ##start encountered, next line is start
	// when ##end encountered, next line is end
	// lines containing one # are ignored
	t_obj obj;
	ft_bzero(&obj, sizeof(obj));
	copy_string_input(&obj);
	print_string_input(&obj);
	delete_string_list(&obj, &(obj.string));
	print_string_input(&obj);

	// iterate through string_list to validate data
	// populate t_room list with data from string_list
	// read data from string

}


void			delete_string_list(t_obj *obj, t_str **list)
{
	if (*list != NULL)
	{
		if ((*list)->next)
			delete_string_list(obj, &(*list)->next);
		ft_memdel((void*)&(*list)->str);
		ft_memdel((void*)&(*list));
		*list = NULL;
	}
}




void			copy_string_input(t_obj *obj)
{
	char		*str;
	t_str		*temp;

	temp = NULL;
	// every call to gnl() will change str's address
	// but each node will have a copy of every new
	// address that str has changed to
	gnl_with_newline(0, &str);
	if (str)
	{
		STRING = malloc(sizeof(t_str));
		STRING->str = str;
		STRING->beginning = STRING;
		STRING->next = NULL;
		while (gnl_with_newline(0, &str) > 0)
		{
			temp = malloc(sizeof(t_str));
			temp->str = str;
			temp->beginning = STRING->beginning;
			temp->next = NULL;
			STRING->next = temp;
			STRING = temp;
		}
		STRING = STRING->beginning;
	}
}

// using printf to print to screen
void		print_string_input(t_obj *obj)
{
	if (STRING != NULL)
	{
		while (STRING->next != NULL)
		{
			printf("addr:%p string:%s", STRING, (STRING->str));
			STRING = STRING->next;
		}
		STRING = STRING->beginning;
	}
	printf("STRING:%p\n", STRING);
}

// check strings with first character '#', which could be command or comment
int				validate_comment(char *str)
{
	if (ft_strcmp(str, "##start") == 0)
		return (2);
	else if (ft_strcmp(str, "##end") == 0)
		return (3);
	else
		return (1);
}



// only content in str describing links between rooms should be digit dash digit: 0-2
int				validate_links(char *str)
{
	int			i;
	int			dash;

	i = 0;
	dash = 0;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '-') || (i == 0 && str[i] == '-'))
			return (0);
		if (str[i] == '-')
			++dash;
		++i;
	}
	if (dash > 1)
		return (0);
	return (1);
}


// ensure that original input is validated
int				validate_string_list(char *str)
{
	int			i;
	int			spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		// check if everything is a printable char, and not ' ' as first character
		if (str[i] == '\n' && (!ft_isprint(str[i]) || (i == 0 && str[i] == ' ')))
			return (0);

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
		if (spaces > 0 && !ft_isdigit(str[i]))
			return (0);
		++i;
	}
	// every line should have two spaces or should be a str describing links between rooms
	if (spaces != 2)
		return (validate_links(str));
	return (1);
}




int				create_lnkd_list(char *str, t_obj *obj)
{
	char		*h;

	// copy current string, malloc and store in obj
	// though it will not contain the newline character

	// INPUT_STR = ft_strjoin(str, INPUT_STR);
	ft_strdel(&h);

	// check if comment or start/end
	if (ft_strcmp("##start", str))
		printf("hello\n");
}


int				get_input(t_obj *obj)
{
	char		*str;

	// first line is a digit check
	// get_next_line(0, &str);
	if (!ft_isdigit(ft_atoi(obj->string)))
	{
		ft_putstr_fd("Error, first line not a digit or has zero ants\n", 0);
		return (0);
	}
	ANTS = ft_atoi(str);

	// continue checking next lines
	while (gnl_with_newline(0, &str) > 0)
	{
		int i = validate_string_list(str);


		if (validate_string_list(str))
			create_lnkd_list(str, obj);
		else
		{
			delete_lnkd_list(obj);
			ft_putstr_fd("Error, not valid map\n", 2);
			return (0);
		}
		

	}
	return (1);
}