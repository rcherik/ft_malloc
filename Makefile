# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/20 20:42:44 by rcherik           #+#    #+#              #
#    Updated: 2015/03/19 13:55:06 by rcherik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
CFLAGS = gcc -Wall -Wextra -Werror -fPIC
IFLAGS = -I includes
DFLAGS = gcc -shared -o
PATH_SRC = src
PATH_OBJ = obj
SRC = show_alloc_mem.c\
	  realloc.c\
	  free.c\
	  malloc.c\
	  ft_printaddr.c\
	  ft_memcpy.c\
	  ft_putchar.c\
	  ft_putstr.c\
	  ft_putendl.c\
	  ft_putnbr.c\
	  ft_bzero.c\

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all : $(NAME)

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(IFLAGS) -o $@ -c $^

$(NAME) : $(OBJ)
	@echo "\033[32m[ malloc objects done ]\033[00m"
	@$(DFLAGS) $(NAME) $(OBJ)
	@ln -sf $(NAME) libft_malloc.so
	@echo "\033[32m[ malloc compiled ]\033[00m"

clean :
	@rm -f $(OBJ)
	@rm -f libft_malloc.so
	@rm -rf $(PATH_OBJ)
	@echo "\033[31m[ malloc : objects deleted ]\033[00m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[31m[ malloc : lib deleted ]\033[00m"

re : fclean all

.PHONY : fclean re clean all
