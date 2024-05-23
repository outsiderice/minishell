# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 18:06:24 by amagnell          #+#    #+#              #
#    Updated: 2024/05/23 08:48:09 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#	TARGET									#
#-------------------------------------------#
NAME = libft.a

#-------------------------------------------#
#	INGREDIENTS								#
#-------------------------------------------#
SRC_DIR 	=	src
SRCS 		=	src/ft_isalpha.c \
				src/ft_isdigit.c \
				src/ft_isalnum.c \
				src/ft_isascii.c \
				src/ft_isprint.c \
				src/ft_strlen.c \
				src/ft_memset.c \
				src/ft_bzero.c \
				src/ft_memcpy.c \
				src/ft_memmove.c \
				src/ft_strlcpy.c \
				src/ft_strlcat.c \
				src/ft_toupper.c \
				src/ft_tolower.c \
				src/ft_strchr.c \
				src/ft_strrchr.c\
				src/ft_strncmp.c\
				src/ft_memchr.c \
				src/ft_memcmp.c \
				src/ft_strnstr.c \
				src/ft_atoi.c \
				src/ft_calloc.c \
				src/ft_strdup.c \
				src/ft_substr.c \
				src/ft_strjoin.c \
				src/ft_strtrim.c \
				src/ft_putchar_fd.c \
				src/ft_putstr_fd.c \
				src/ft_putendl_fd.c \
				src/ft_putnbr_fd.c \
				src/ft_striteri.c \
				src/ft_strmapi.c \
				src/ft_itoa.c \
				src/ft_split.c \
				src/ft_printf.c \
				src/ft_nbrs.c \
				src/ft_putchar.c \
				src/ft_putnbr.c \
				src/ft_putptr.c \
				src/ft_putstr.c \
				src/ft_putunbr.c \
				src/ft_sort_format.c

BUILD_DIR 	= .build
OBJS 		= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS 		= $(OBJS:%.o=%.d)

CC  		= clang
CFLAGS 		= -Wall -Wextra -Werror
CPPFLAGS 	= -MMD -MP -I include
AR 			= ar
ARFLAGS		= -r -c -s

#-------------------------------------------#
#	UTILS									#
#-------------------------------------------#
RM = rm -f
MAKEFLAGS += --no-print-directory
DIR_DUP =  mkdir -p $(@D)

#-------------------------------------------#
#	RECIPES									#
#-------------------------------------------#
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
	$(info Created $(NAME))
	
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(call DIR_DUP,$(@D))
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info Created $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#-------------------------------------------#
#	SPECIAL RULES							#
#-------------------------------------------#

.PHONY: all re clean fclean
.SILENT: