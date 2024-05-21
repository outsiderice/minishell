# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 10:02:57 by amagnell          #+#    #+#              #
#    Updated: 2024/05/21 09:04:46 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#	TARGET									#
#-------------------------------------------#
NAME := minishell

#-------------------------------------------#
#	INGREDIENTS								#
#-------------------------------------------#
LIBS		:=	ft readline termcap
LIBFT_DIR	:=	lib/libft
RDLINE_DIR	:=	lib/readline
LIBFT		:=	lib/libft/libft.a
RDLINE		:=	lib/readline/libreadline.a
RDLINEHIS	:=	lib/readline/libhistory.a
LIBS_TARGET	:=	$(LIBFT) $(RDLINE) $(RDLINEHIS)

INCS		:=	inc	\
				lib/libft/include

SRC_DIR		:=	src
SRCS 		:=	src/main.c \
				src/get_input.c \
				src/check_input.c \
				src/tokenize.c

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
all: libft readline $(NAME)

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info Created $@)

libft:
	$(MAKE) $(MAKEFLAGS) -C $(LIBFT_DIR)

readline:
	@if [ ! -f $(RDLINE_DIR)config.status ]; then\
		cd $(RDLINE_DIR) && ./configure &> /dev/null; \
	fi
	$(MAKE) $(MAKEFLAGS) -C $(RDLINE_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -D READLINE_LIBRARY=1 -c -o $@ $<
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

.PHONY: all re clean fclean libft readline
.SILENT: