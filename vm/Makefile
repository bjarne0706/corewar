# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstepane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 15:30:45 by dstepane          #+#    #+#              #
#    Updated: 2019/05/16 15:30:47 by dstepane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../corewar
CC			= gcc
FLAGS		= -g -Wall -Wextra -Werror

SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
INC_DIR		= ./inc/

LIB_DIR		= ../libft/
LIBFT 		= $(LIB_DIR)libft.a
LIB_INC		= $(LIB_DIR)includes/

SRC			=	vm_main.c \
				init.c \
				parse_flags.c \
				parse_players.c \
				parse_players2.c \
				game.c \
				cycle.c \
				parse_op_args.c \
				printer.c \
				utils.c \
				utils2.c \
				carriages.c \
				byebye.c \
				op_live.c \
				op_ld.c \
				op_st.c \
				op_add.c \
				op_sub.c \
				op_and.c \
				op_or.c \
				op_xor.c \
				op_zjmp.c \
				op_ldi.c \
				op_sti.c \
				op_fork.c \
				op_lld.c \
				op_aff.c \
				op_lldi.c \
				op_lfork.c \
				logs.c \
				vs_ncurses.c \
				vs_1.c \
				vs_2.c \
				vs_3.c \
				vs_4.c 

OBJ 		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) -lncurses $(OBJ) -lft -L $(LIB_DIR) -o $(NAME)
	@echo "\033[32m\033[100m\033[1mCorewar executable compiled.\033[0m"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(INC_DIR)vm.h ../op.h
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIB_INC)
	@echo "	\033[96m$@\033[0m"

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mCorewar object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mCorewar executable removed.\033[0m"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
