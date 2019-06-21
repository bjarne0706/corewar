# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchantse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 14:11:02 by dchantse          #+#    #+#              #
#    Updated: 2019/05/13 14:11:04 by dchantse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = asm_main.c addict_for_all.c addict_for_handel_exec_code.c\
			addict_for_read_asm.c addict_for_read_asm_p2.c\
			addict_func_for_read_asm.c addit_for_writes.c\
			find_op_and_fill_args.c handle_exec_code.c\
			read_asm.c writes.c 

NAME		= ../asm
CC			= gcc
FLAGS		= -g -Wall -Wextra -Werror

SRC_DIR		= 
OBJ_DIR		= 
INC_DIR		= 

LIB_DIR		= ../libft/
LIBFT 		= $(LIB_DIR)libft.a
LIB_INC		= $(LIB_DIR)includes/

OBJ 		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) -lncurses $(OBJ) -lft -L $(LIB_DIR) -o $(NAME)
	@echo "\033[32m\033[100m\033[1mASM executable compiled.\033[0m"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(INC_DIR)vm.h ../op.h
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIB_INC)
	@echo "	\033[96m$@\033[0m"

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@echo "\033[31mASM object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@@make fclean -C $(LIB_DIR)
	@echo "\033[31mASM executable removed.\033[0m"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
