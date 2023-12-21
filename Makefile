# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marschul <marschul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:57:25 by ***REMOVED***             #+#    #+#              #
#    Updated: 2023/12/21 15:47:23 by marschul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC 		:= cc
# CFLAGS 	:= -Wall -Wextra -Werror
DFLAGS 	:= -g3
DNAME 	:= minishell_debug
HEADERS = -I./includes -I ./libs/libft/includes

SRCDIR		:= src
OBJDIR		:= objs
LIB 		:= libs/libft/libft.a -lreadline
LIB_DEBUG := libs/libft/libft_debug.a -lreadline

SRCS 	:= $(SRCDIR)/minishell.c $(SRCDIR)/helper_functions.c \
$(SRCDIR)/input_handling/input_utils.c \
$(SRCDIR)/parsing/parsing_main.c $(SRCDIR)/parsing/parsing_utils.c \
$(SRCDIR)/builtins/cd.c $(SRCDIR)/builtins/echo.c $(SRCDIR)/builtins/export.c $(SRCDIR)/builtins/pwd.c $(SRCDIR)/builtins/env.c $(SRCDIR)/builtins/unset.c
# $(SRCDIR)/execute_line/execute_line.c

OBJS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DOBJS   := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d.o,$(SRCS))
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/input_handling $(OBJDIR)/parsing $(OBJDIR)/builtins $(OBJDIR)/execute_line)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR)/%.d.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(DFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libs/libft
	$(CC) $(CFLAGS) $(LIB) $(HEADERS) $(OBJS) -o $(NAME)

debug: $(DOBJS)
	make -C libs/libft debug
	$(CC) $(CFLAGS) $(DFLAGS) $(LIB_DEBUG) $(HEADERS) $(DOBJS) -o $(DNAME)

testexecute:
	make -C libs/libft
	gcc -Wall -Werror -g  -Llibs/libft -lft $(HEADERS) $(SRCDIR)/execute_line/execute_line.c $(SRCDIR)/builtins/echo.c $(SRCDIR)/builtins/cd.c $(SRCDIR)/builtins/env.c $(SRCDIR)/builtins/unset.c $(SRCDIR)/builtins/export.c $(SRCDIR)/builtins/pwd.c $(SRCDIR)/helper_functions.c

clean:
	make -C libs/libft clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C libs/libft fclean
	rm -rf $(NAME) $(DNAME)

re: fclean all

.PHONY: all, clean, fclean, re, debug
