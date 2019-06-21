# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstepane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 17:35:29 by dstepane          #+#    #+#              #
#    Updated: 2019/06/21 17:35:31 by dstepane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C ./ass
	@make -C ./vm

clean:
	@make clean -C ./ass
	@make clean -C ./vm

fclean: clean
	@make fclean -C ./ass
	@make fclean -C ./vm

re: fclean all

.PHONY: all clean fclean re
