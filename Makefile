# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 10:02:57 by amagnell          #+#    #+#              #
#    Updated: 2024/08/04 15:45:51 by kkoval           ###   ########.fr        #
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
				lib/libft

SRC_DIR		=	src
SRCS 		=	src/main.c \
				src/signals.c \
				src/error.c \
				src/free.c \
				src/get_input.c \
				src/parsing/check_quotes.c \
				src/parsing/parser.c \
				src/parsing/expand.c \
				src/parsing/expand_utils.c \
				src/parsing/tokenize.c \
				src/parsing/token_utils.c \
				src/parsing/tokens_lst_utils.c \
				src/env_handler.c \
				src/env2.c\
				src/prep_execution.c \
				src/prep_utils.c \
				src/execution.c \
				src/exec_1.c \
				src/exec_2.c \
				src/exec_utils.c \
				src/builtins/handle_builtins.c \
				src/builtins/pwd.c \
				src/builtins/env.c \
				src/builtins/builtins_utils.c \
				src/builtins/exit.c \
				src/builtins/echo.c \
				src/builtins/unset.c \
				src/builtins/export.c \
				src/builtins/cd.c \
				src/heredoc.c \
				src/heredoc_expansion.c \
				src/env_utils.c

BUILD_DIR 	=	.build
OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		=	$(OBJS:%.o=%.d)

CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror
CPPFLAGS 	=	$(addprefix -I, $(INCS)) -MMD -MP
LDFLAGS		=	$(addprefix -L, $(dir $(LIBS_TARGET)))
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
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -fsanitize=address -o $(NAME) #
	$(info Created $@)

libft:
	@make $(MAKEFLAGS) -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) Makefile
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -D READLINE_LIBRARY=1
	$(info Created $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

#-------------------------------------------#
#	SPECIAL RULES							#
#-------------------------------------------#

.PHONY: all re clean fclean libft #readline
.SILENT: