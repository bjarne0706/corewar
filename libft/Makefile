# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstepane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 20:40:47 by dstepane          #+#    #+#              #
#    Updated: 2018/10/25 20:40:49 by dstepane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
CC 			= gcc
FLAGS 		= -g -Wall -Wextra -Werror
HEADS 		= ./includes/

SRC_DIR		= ./srcs/
SRC_NAME	=	ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_memcmp.c \
				ft_memchr.c \
				ft_strlen.c \
				ft_strdup.c \
			 	ft_strcpy.c \
			 	ft_strncpy.c \
			 	ft_strcat.c \
			 	ft_strncat.c \
				ft_strlcat.c \
				ft_strchr.c \
			 	ft_strrchr.c \
			 	ft_strstr.c \
			 	ft_strnstr.c \
				ft_strcmp.c \
				ft_strncmp.c \
			 	ft_atoi.c \
			 	ft_isalpha.c \
			 	ft_isdigit.c \
			 	ft_isalnum.c \
			 	ft_isascii.c \
			 	ft_isprint.c \
				ft_toupper.c \
			 	ft_tolower.c \
			 	ft_memalloc.c \
				ft_memdel.c \
				ft_strnew.c \
				ft_strdel.c \
			 	ft_strclr.c \
			 	ft_striter.c \
			 	ft_striteri.c \
			 	ft_strmap.c \
			 	ft_strmapi.c \
			 	ft_strequ.c \
			 	ft_strnequ.c \
			 	ft_strsub.c \
			 	ft_strjoin.c \
				ft_strtrim.c	\
				ft_strsplit.c \
			 	ft_itoa.c \
				ft_putchar.c \
			 	ft_putstr.c \
				ft_putendl.c \
			 	ft_putnbr.c \
			 	ft_putchar_fd.c \
				ft_putstr_fd.c \
			 	ft_putendl_fd.c \
			 	ft_putnbr_fd.c \
			 	ft_lstnew.c \
				ft_lstdelone.c \
				ft_lstdel.c \
				ft_lstadd.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_strrev.c \
				ft_sort_integer_table.c \
				ft_range.c \
				ft_recursive_power.c \
				ft_sqrt.c \
				get_next_line.c \
				ft_isblank.c \
				ft_isspace.c \
				ft_isint.c

PRINTF_DIR 	=	./ft_printf/
PRINTF_SRC 	=	ft_printf.c \
				parser.c \
				convert_c_percent.c \
				convert_s.c \
				convert_di.c \
				convert_di2.c \
				convert_u.c \
				convert_o.c \
				convert_x.c \
				convert_p.c \
				convert_f.c \
				convert_f2.c \
				convert_b.c \
				colors1.c \
				colors2.c \
				colors3.c \
				pf_itoa_base.c \
				pf_strjoin.c

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME)) $(addprefix $(PRINTF_DIR), $(PRINTF_SRC))

OBJ_DIR	= ./obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o)) $(addprefix $(OBJ_DIR), $(PRINTF_SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[32m\033[1mlibft.a compiled and indexed.\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@ -I $(HEADS)
	@echo "\033[96m	$@\033[0m"


$(OBJ_DIR)%.o: $(PRINTF_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@ -I $(HEADS)
	@echo "\033[96m	$@\033[0m"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mLibft object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mlibft.a removed.\033[0m"
	
re: fclean all

.PHONY: all clean fclean re
