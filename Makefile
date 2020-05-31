# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/03 16:52:44 by bprado        #+#    #+#                  #
#    Updated: 2020/05/31 17:57:03 by macbook       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in
CFLAGS		= -Wall -Wextra -Werror
SRC 		=	src/lem-in.c \
				src/print_functions.c \
				src/create_lnkd_lists.c \
				src/validate_functions.c \
				src/delete_functions.c \
				src/solver.c
LIB 		= ./libft
LIB_A		= ./libft/libft.a
PFLIB		= ./ft_printf
PFLIB_A		= ./ft_printf/libftprintf.a
INC 		= -I inc -I libft/inc -I ft_printf/inc
OBJ			= $(patsubst src/%.c,obj/%.o,$(SRC))
CC			= gcc

# Colors
PURPLE		= \033[95m
CYAN		= \033[96m
DARKCYAN	= \033[36m
BLUE		= \033[94m
GREEN		= \033[92m
YELLOW		= \033[93m
RED			= \033[91m
END			= \033[0m

# tput commands
BOLD		:= `tput bold`
UNDERLINE	:= `tput smul`
END_TPUT	:= `tput sgr0`

all: $(NAME)

begin_statement:
	@printf "$(BOLD) *** Compiling $(NAME) ***$(END_TPUT)\n"

$(NAME): begin_statement $(OBJ) ft_printf/libftprintf.a
	@$(CC) -o $@ $(CFLAGS) $(INC) $(OBJ) $(PFLIB_A)
	@printf " $(CYAN)$(BOLD)$(UNDERLINE)./$(NAME)$(END)$(END_TPUT) created\n"

obj/%.o: src/%.c inc/ft_lem-in.h
	@mkdir -p obj
	@printf " $(GREEN)$(BOLD)✔$(END)$(END_TPUT) Object file for $(PURPLE)$<$(END)\n"
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

ft_printf/libftprintf.a: $(wildcard ft_printf/*.c)
	@$(MAKE) -C $(PFLIB)

clean:
	@printf "Cleaning $(YELLOW)$(BOLD)$(NAME)$(END)$(END_TPUT)...\n"
	@make clean -C $(LIB)
	@rm -rf obj

fclean:	clean
	@make fclean -C $(PFLIB)
	@rm -rf $(NAME) test

test: test.c $(NAME)
	@$(CC) -o $@ -Wall -Wextra -g $(INC) $^

re:	fclean all
