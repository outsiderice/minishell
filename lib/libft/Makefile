# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 18:06:24 by amagnell          #+#    #+#              #
#    Updated: 2024/05/23 16:27:53 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#  TARGET                                   #
#-------------------------------------------#
NAME = libft.a

#-------------------------------------------#
#   INGREDIENTS                             #
#-------------------------------------------#
SRCS 		=	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c\
				ft_strncmp.c\
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_striteri.c \
				ft_strmapi.c \
				ft_itoa.c \
				ft_split.c \

B_SRCS		=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

BUILD_DIR	= .build/
OBJS 		= $(SRCS:%.c=$(BUILD_DIR)%.o)
B_OBJS		= $(B_SRCS:%.c=$(BUILD_DIR)%.o)

DEPS 		= $(OBJS:.o=.d)
B_DEPS		= $(B_OBJS:.o=.d)

CC  		= gcc
CFLAGS 		= -Wall -Wextra -Werror
CPPFLAGS 	= -MMD -MP -I include
AR 			= ar
ARFLAGS		= -r -c -s

#-------------------------------------------#
#  UTILS                                    #
#-------------------------------------------#
RM 			= rm -rf
MKFLAGS		+= --no-print-directory
MKDIR		= mkdir -p

#-------------------------------------------#
#   RECIPES                                 #
#-------------------------------------------#
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "\nLibft compiled!"

$(BUILD_DIR)%.o: %.c Makefile
	@$(MKDIR) $(BUILD_DIR)
	@printf "#"
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

bonus: fclean $(OBJS) $(B_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(B_OBJS)
	
-include $(DEPS) $(B_DEPS)
#-------------------------------------------#
#   SPECIAL RULES                           #
#-------------------------------------------#
clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all re clean fclean bonus
.SILENT:
