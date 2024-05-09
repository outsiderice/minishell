# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 10:02:57 by amagnell          #+#    #+#              #
#    Updated: 2024/05/09 13:13:56 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#	TARGET									#
#-------------------------------------------#
NAME := minishell

#-------------------------------------------#
#	INGREDIENTS								#
#-------------------------------------------#
LIBS		:=	ft
LIBS_FOLDER	:=	lib/libft
LIBS_TARGET	:=	lib/libft/libft.a

INCS		:=	inc	\
				lib/libft/include

SRC_DIR		:=	src
SRCS 		:=	src/main.c

BUILD_DIR 	:=	.build
OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:=	$(OBJS:%.o=%.d)

CC 			:=	gcc
CFLAGS 		:=	-Wall -Wextra -Werror
CPPFLAGS 	:=	$(addprefix -I, $(INCS)) -MMD -MP
LDFLAGS		:=	$(addprefix -L, $(dir $(LIBS_TARGET)))
LDLIBS		:=	$(addprefix -l, $(LIBS))

#-------------------------------------------#
#	UTILS									#
#-------------------------------------------#
RM 			:=	rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		=	mkdir -p $(@D)

#-------------------------------------------#
#	RECIPES									#
#-------------------------------------------#
all: libft $(NAME)

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info Created $@)

libft:
	$(MAKE) -C $(LIBS_FOLDER)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info Created $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#-------------------------------------------#
#	SPECIAL RULES							#
#-------------------------------------------#

.PHONY: all re clean fclean libft