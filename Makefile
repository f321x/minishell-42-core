# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:57:25 by ***REMOVED***             #+#    #+#              #
#    Updated: 2023/12/18 13:54:59 by ***REMOVED***            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC 		:= cc
# CFLAGS 	:= -Wall -Wextra -Werror
DFLAGS 	:= -g3
DNAME 	:= minishell_debug
HEADERS = -I./includes

SRCDIR	:= src
OBJDIR	:= objs
LIBDIR	:= libs

SRCS 	:= $(SRCDIR)/minishell.c \
$(SRCDIR)/input_handling/input_utils.c

OBJS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DOBJS   := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d.o,$(SRCS))
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/input_handling)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR)/%.d.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(DFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBDIR)/libft
	$(CC) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME)

debug: $(DOBJS)
	make -C $(LIBDIR)/libft debug
	$(CC) $(CFLAGS) $(DFLAGS) $(HEADERS) $(DOBJS) -o $(DNAME)

clean:
	make -C $(LIBDIR)/libft clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C $(LIBDIR)/libft fclean
	rm -rf $(NAME) $(DNAME)

re: fclean all

.PHONY: all, clean, fclean, re, debug
