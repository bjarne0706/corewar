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

NAME = asm

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

.SILENT:

SRC_NAME = asm_main.c addict_for_all.c addict_for_handel_exec_code.c\
			addict_for_read_asm.c addict_for_read_asm_p2.c\
			addict_func_for_read_asm.c addit_for_writes.c\
			find_op_and_fill_args.c handle_exec_code.c\
			read_asm.c writes.c 

OBJ  = $(patsubst %.c,%.o,$(SRC_NAME))

$(NAME): $(OBJ)
	make -C ../libft
	gcc $(FLAGS) $(SRC_NAME) -I include -lft -L.././libft/ -o $(NAME)

obj/%.o:%.c
	 $(CC) $< -o $@ $(FLAGS) $(HDR)

clean:
	rm -rf *.o
	make clean -C ../libft

fclean: clean
	rm -rf $(NAME) ../libft.a
	make fclean -C ../libft

re: fclean all
