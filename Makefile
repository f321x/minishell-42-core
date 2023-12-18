# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:57:25 by ***REMOVED***             #+#    #+#              #
#    Updated: 2023/12/18 09:05:01 by ***REMOVED***            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC 		:= cc
CFLAGS 	:= -Wall -Wextra -Werror
DFLAGS 	:= -g3
DNAME 	:= minishell_debug
HEADERS = -I./includes

SRCDIR	:= src
OBJDIR	:= objs
LIBDIR	:= libs

SRCS 	:= builtins/***.c

OBJS	:= $(addprefix $(OBJDIR)/, $(notdir ${SRCS:.c=.o}))
DOBJS   := $(addprefix $(OBJDIR)/, $(notdir ${SRCS:.c=.d.o}))
$(shell mkdir -p $(OBJDIR))

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
