# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 12:28:22 by pgritsen          #+#    #+#              #
#    Updated: 2017/11/15 13:00:38 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

CFLAGS	=	-Wextra -Werror -Wall

OFLAGS	=	-I.

NAME	=	fillit

HEADERS	=	fillit.h

SRC		=	heart.c validate.c

OBJDIR	=	obj

OBJ		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ): $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(OFLAGS)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
