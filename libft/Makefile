# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 14:16:27 by ctrouve           #+#    #+#              #
#    Updated: 2022/09/22 14:13:37 by ctrouve          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BLACK=\033[30m
RED=\033[0;31m
BOLDRED=\033[1;31m
GREEN=\033[0;32m
BOLDGREEN=\033[1;32m
YELLOW=\033[0;33m
BOLDYELLOW=\033[1;33m
BLUE=\033[0;34m
BOLDBLUE=\033[1;34m
PINK=\033[0;35m
BOLDPINK=\033[1;35m
CYAN=\033[0;36m
BOLDCYAN=\033[1;36m
WHITE=\033[37m
NORMAL=\033[0m

LIBC_SRC = ft_abs.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_count_splits_str.c \
		ft_find_next_str.c \
		ft_imax.c \
		ft_imin.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_is_whitespace.c \
		ft_max_d.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_ndigits.c\
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		ft_realloc.c \
		ft_sqrt.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtod.c\
		ft_strtok.c\
		ft_strtrim.c \
		ft_swap.c \
		ft_swap_d.c \
		ft_tabledel.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c

LIST_SRC = ft_lstadd.c\
		ft_lstappend.c\
		ft_lstdel.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstnew.c

VEC3_SRC = ft_add_vec3.c\
		ft_div_vec3.c\
		ft_dot_vec3.c\
		ft_invert_vec3.c\
		ft_len_vec3.c\
		ft_make_vec3.c\
		ft_mul_vec3.c\
		ft_mul_vec3_vec3.c\
		ft_normalize_vec3.c\
		ft_reflect_vec3.c\
		ft_set_vec3.c\
		ft_sub_vec3.c\
		ft_cross_vec3.c\
		ft_rotate_vec3.c\
		ft_parse_vec3.c

COLOR_SRC = ft_add_rgba.c\
		ft_clamp_rgba.c\
		ft_get_color.c\
		ft_lerp_rgba.c\
		ft_make_rgba.c\
		ft_mul_rgba.c\
		ft_mul_rgba_rgba.c\
		ft_sub_rgba.c\
		ft_parse_rgba.c\
		ft_blend_rgba.c\
		ft_intensity_rgba.c

SRCDIR = sources

LIBC_SRCDIR = $(SRCDIR)/libc
LIST_SRCDIR = $(SRCDIR)/list
VEC3_SRCDIR = $(SRCDIR)/vector
COLOR_SRCDIR = $(SRCDIR)/color

SRCS = $(addprefix $(LIBC_SRCDIR)/, $(LIBC_SRC))\
		$(addprefix $(LIST_SRCDIR)/, $(LIST_SRC))\
		$(addprefix $(VEC3_SRCDIR)/, $(VEC3_SRC))\
		$(addprefix $(COLOR_SRCDIR)/, $(COLOR_SRC))

OBJECTS	= $(notdir $(SRCS:.c=.o))

INCL = includes

all: $(NAME)

$(NAME):
	@echo "$(BOLDYELLOW)Making $(NAME) $(NORMAL)"
	@gcc -Wall -Wextra -Werror -I $(INCL) -c $(SRCS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "$(YELLOW)Done $(NORMAL)"

clean:
	@echo "$(BOLDBLUE)Removing objects *.o $(NORMAL)"
	@rm -f $(OBJECTS)
	@echo "$(BOLDBLUE)Done $(NORMAL)"

fclean: clean
	@echo "$(BOLDPINK)Removing $(NAME) $(NORMAL)"
	@rm -f $(NAME)
	@echo "$(BOLDPINK)Done $(NORMAL)"

re: fclean all

.PHONY: all clean fclean re
