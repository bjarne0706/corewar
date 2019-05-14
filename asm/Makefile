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

FLAGS = -Werror -Wextra -Wall

all: $(NAME)

.SILENT:

SRC_NAME = asm_main.c

OBJ  = $(patsubst %.c,%.o,$(SRC_NAME))

$(NAME): $(OBJ)
	make -C ../libft
	gcc $(FLAGS) *.c -I include -lft -L.././libft/ -o $(NAME)

obj/%.o:%.c
	 $(CC) $< -o $@ $(FLAGS) $(HDR)

clean:
	rm 42.cor
	rm -rf *.o
	make clean -C ../libft

fclean: clean
	rm -rf $(NAME) ../libft.a
	make fclean -C ../libft

re: fclean all
