# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/13 16:43:23 by ecunniet          #+#    #+#              #
#    Updated: 2016/12/13 16:43:29 by ecunniet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIBPATH = libft
LIBNAME = libft.a
LIB = $(LIBNAME:%=$(LIBPATH)/%)
CFLAGS = -Wall -Werror -Wextra -I$(LIBPATH)/includes
LDFLAGS = -L $(LIBPATH) -l$(LIBNAME:lib%.a=%)
CC = gcc
SRC	= ft_error.c Fdf.c
INC = fdf.h
OBJ	= $(SRC:%.c=%.o)

all: $(NAME) 

$(LIB):
	$(MAKE) -C $(LIBPATH)

$(NAME): $(OBJ) $(LIB)
	$(CC) -o $@ $(LDFLAGS) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBPATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBPATH)

re: fclean
	$(MAKE) all

norme:
	@norminette $(SRC) $(INC)
	@$(MAKE) norme -C $(LIBPATH)

.PHONY: all clean fclean re norme
