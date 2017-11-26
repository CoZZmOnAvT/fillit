# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 12:28:22 by pgritsen          #+#    #+#              #
#    Updated: 2017/11/26 13:50:03 by pgritsen         ###   ########.fr        #
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

lib:
	@make -C $(LIBFOLDER)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFOLDER)/libft.a $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFOLDER)/libft.a

$(OBJ): $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	make -C $(LIBFOLDER) clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C $(LIBFOLDER) fclean
	rm -rf $(NAME)

re:	fclean all
