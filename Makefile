# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 12:28:22 by pgritsen          #+#    #+#              #
#    Updated: 2017/11/26 14:42:08 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wextra -Werror -Wall

NAME		=	fillit

HEADERS		=	fillit.h

SRC			=	heart.c bit_operations.c input.c figures.c alcorythm_x.c	\
				helpers.c row_operations.c output.c container.c

LIBFOLDER	=	libft

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFOLDER)/libft.a $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFOLDER)/libft.a

$(LIBFOLDER)/libft.a: lib

lib:
	make -C $(LIBFOLDER)

$(OBJ): $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	make -C $(LIBFOLDER) clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C $(LIBFOLDER) fclean
	rm -rf $(NAME)

re:	fclean all

.DEFAULT:
	@echo "usage:\n\t-make\n\t-make fillit\n\t-make clean\n\t-make fclean\n\t-make re"

.PHONY: build clean fclean
