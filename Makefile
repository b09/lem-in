# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/03 16:52:44 by bprado        #+#    #+#                  #
#    Updated: 2020/06/25 17:45:46 by bprado        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

# CFLAGS		= -Wall -Wextra -Werror

SRC 		=	src/lem_in.c \
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

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

all: $(NAME)

# begin_statement:
# 	@printf "$(BOLD) *** Compiling $(NAME) ***$(END_TPUT)\n"

$(NAME): $(OBJ) ft_printf/libftprintf.a
	@$(CC) -o $@ $(CFLAGS) $(INC) $(OBJ) $(PFLIB_A)
	@printf " $(CYAN)$(BOLD)$(UNDERLINE)./$(NAME)$(END)$(END_TPUT) created\n"

obj/%.o: src/%.c inc/ft_lem-in.h
	@mkdir -p obj
	@printf " $(GREEN)$(BOLD)✔$(END)$(END_TPUT) Object file for \
	$(PURPLE)$(current_dir)/$<$(END)\n"
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

ft_printf/libftprintf.a: $(wildcard ft_printf/*.c)
	@$(MAKE) -C $(PFLIB)

clean:
	@printf "Cleaning$(BOLD)   $(NAME) object files$(END_TPUT)\n"
	@make clean -C $(LIB)
	@rm -rf obj

# fclean:	clean
# 	@make fclean -C $(PFLIB)
# 	@rm -rf $(NAME) test

# removed prerequisite of clean to fclean to eliminte repeated printf text
fclean:
	@printf "Cleaning$(BOLD)   $(NAME) object files$(END_TPUT)\n"
	@printf "Deleting$(YELLOW)$(BOLD)   ./$(NAME)$(END) binaries$(END_TPUT)\n"
	@rm -rf obj
	@rm -rf $(wildcard *.dSYM)
	@make fclean -C $(PFLIB)
	@printf "$(GREEN)$(BOLD)Complete!$(END)$(END_TPUT)\n"

test: test.c $(NAME)
	@$(CC) -o $@ -Wall -Wextra -g $(INC) $^

re:	fclean all
