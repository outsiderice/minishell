# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 10:02:57 by amagnell          #+#    #+#              #
#    Updated: 2024/05/09 11:21:45 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------#
#        TARGET              #
#----------------------------#
NAME		:=	eggshell

#----------------------------#
#       INGREDIENTS          #
#----------------------------#
LIBS		:=	readline
L_RDLINE	:=	lib/readline
LIBS_TARGET	:=	lib/readline/libreadline.a \
				lib/readline/libhistory.a

INC			:=	inc \
				lib/readline/%.h

SRC_DIR		:=	src
SRCS		:=	src/main.c

BUILD_DIR	:=	.build
OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:=	$(OBJS:%.o=%.d)

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
CPPFLAGS	:=	-MMD -MP
LDFLAGS		:=	$(addprefix -I, $(INC)) -MMD -MP
LDLIBS		:= 	$(addprefix -l, $(LIBS))

DIR_DUP		:=	mkdir -p $(@D)

#---------------------------#
#       COMPILATION         #
#---------------------------#
all : 
	$(MAKE) $(NAME)

$(NAME) : $(LIBS_TARGET) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

#---------------------------#
#       OTHER RULES         #
#---------------------------#
clean	:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	rm -f $(OBJS) $(DEPS)

fclean	: clean
	rm -f $(NAME)
	
re		:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re

.SILENT:
