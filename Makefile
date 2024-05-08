# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 10:02:57 by amagnell          #+#    #+#              #
#    Updated: 2024/05/08 13:04:23 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------#
#		VARIABLES			#
#---------------------------#

NAME	= eggshell

SRCS	= src/main.c

OBJS	=

#---------------------------#
#		COMPILATION			#
#---------------------------#

$(NAME)	: $(OBJS)

#---------------------------#
#		COMMANDS			#
#---------------------------#

.PHONY: all clean fclean re

all		: $(NAME)

clean	:
	rm -f $(OBJS) $(DEPS)

fclean	: clean
	rm -f $(NAME)
	
re		:
	$(MAKE) fclean
	$(MAKE) all
