# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 10:02:57 by amagnell          #+#    #+#              #
#    Updated: 2024/06/11 16:58:47 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#	TARGET									#
#-------------------------------------------#
NAME = minishell

#-------------------------------------------#
#	INGREDIENTS								#
#-------------------------------------------#
LIBS		=	ft readline termcap
LIBFT_DIR	=	lib/libft
LIBFT		=	lib/libft/libft.a
LIBS_TARGET	=	$(LIBFT)

INCS		=	inc	\
				lib/libft/include

SRC_DIR		=	src
SRCS 		=	src/main.c \
				src/get_input.c \
				src/check_quotes.c \
				src/tokenize.c \
				src/token_utils.c \
				src/tokens_lst_utils.c \
				src/env_handler.c \
				src/parser.c \
				src/prep_execution.c \
				src/execution.c \
				src/exec_prototype.c \
				src/builtins/handle_builtins.c \
				src/builtins/pwd.c \
				src/builtins/env.c \
				src/builtins/builtins_utils.c \
				src/builtins/echo.c

BUILD_DIR 	=	.build
OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		=	$(OBJS:%.o=%.d)

CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -Werror
CPPFLAGS 	=	$(addprefix -I, $(INCS)) -MMD -MP
LDFLAGS		=	$(addprefix -L, $(dir $(LIBS_TARGET))) -no-pie
LDLIBS		=	$(addprefix -l, $(LIBS))

#-------------------------------------------#
#	UTILS									#
#-------------------------------------------#
RM 			=	rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		=	mkdir -p $(@D)

#-------------------------------------------#
#	RECIPES									#
#-------------------------------------------#
all: libft $(NAME) #readline 

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS)  -o $(NAME) #-fsanitize=address
	$(info Created $@)

libft:
	$(MAKE) $(MAKEFLAGS) -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) Makefile
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -D READLINE_LIBRARY=1
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

.PHONY: all re clean fclean libft #readline
.SILENT: