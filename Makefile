# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/03 16:52:44 by bprado        #+#    #+#                  #
#    Updated: 2020/04/20 12:12:06 by macbook       ########   odam.nl          #
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
INC 		= -I inc -I libft/inc
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

$(NAME): begin_statement $(OBJ) libft/libft.a
	@$(CC) -o $@ $(CFLAGS) $(INC) $(OBJ) $(LIB_A)
	@printf " $(CYAN)$(BOLD)$(UNDERLINE)./$(NAME)$(END)$(END_TPUT) created\n"

obj/%.o: src/%.c inc/ft_lem-in.h
	@mkdir -p obj
	@printf " $(GREEN)$(BOLD)✔$(END)$(END_TPUT) Object file for $(PURPLE)$<$(END)\n"
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

libft/libft.a: $(wildcard libft/*.c)
	@$(MAKE) -C $(LIB)

clean:
	@printf "Cleaning $(YELLOW)$(BOLD)$(NAME)$(END)$(END_TPUT)...\n"
	@make clean -C $(LIB)
	@rm -rf obj

fclean:	clean
	@make fclean -C $(LIB)
	@rm -rf $(NAME) test

test: test.c $(NAME)
	@$(CC) -o $@ -Wall -Wextra -g $(INC) $^

re:	fclean all
