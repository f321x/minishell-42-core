# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marschul <marschul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 08:57:25 by ***REMOVED***             #+#    #+#              #
#    Updated: 2024/01/08 11:34:06 by marschul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC 		:= cc
# CFLAGS 	:= -Wall -Wextra -Werror
DFLAGS 	:= -g3 -fsanitize=address
DNAME 	:= minishell_debug
HEADERS = -I./includes -I ./libs/libft/includes

SRCDIR		:= src
OBJDIR		:= objs
TESTDIR		:= test
LIB 		:= libs/libft/libft.a -lreadline
LIB_DEBUG := libs/libft/libft_debug.a -lreadline

SRCS 	:= $(SRCDIR)/minishell.c $(SRCDIR)/helper_functions.c \
$(SRCDIR)/input_handling/input_utils.c \
$(SRCDIR)/parsing/parsing_main.c $(SRCDIR)/parsing/parsing_utils.c $(SRCDIR)/parsing/array_utils.c $(SRCDIR)/parsing/parsing_functions.c $(SRCDIR)/parsing/string_utils.c $(SRCDIR)/parsing/quote_parsing.c $(SRCDIR)/parsing/parsing_env_var.c \
$(SRCDIR)/builtins/cd.c $(SRCDIR)/builtins/echo.c $(SRCDIR)/builtins/export.c $(SRCDIR)/builtins/pwd.c $(SRCDIR)/builtins/env.c $(SRCDIR)/builtins/unset.c $(SRCDIR)/builtins/exit.c\
$(SRCDIR)/execute_line/execute_line.c \
$(SRCDIR)/signals.c

OBJS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DOBJS   := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d.o,$(SRCS))
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/input_handling $(OBJDIR)/parsing $(OBJDIR)/builtins $(OBJDIR)/execute_line)

SRCS_TEST_BUILTINS = $(patsubst $(SRCDIR)/minishell.c, $(TESTDIR)/test_builtins.c , $(SRCS))
SRCS_TEST_FINDFULLPATH = $(patsubst $(SRCDIR)/minishell.c, $(TESTDIR)/test_findfullpath.c , $(SRCS))

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
	gcc -Wall -Wextra  -g -Llibs/libft -lft $(HEADERS) $(SRCDIR)/execute_line/execute_line.c $(SRCDIR)/builtins/echo.c $(SRCDIR)/builtins/cd.c $(SRCDIR)/builtins/env.c $(SRCDIR)/builtins/unset.c $(SRCDIR)/builtins/export.c $(SRCDIR)/builtins/pwd.c $(SRCDIR)/builtins/exit.c $(SRCDIR)/helper_functions.c

testbuiltins: $(SRCS_TEST_BUILTINS)
	make -C libs/libft debug
	$(CC) $(CFLAGS) $(DFLAGS) $(LIB_DEBUG) $(HEADERS) $(SRCS_TEST_BUILTINS) -o $(TESTDIR)/testbuiltins

testfindfullpath: $(SRCS_TEST_FINDFULLPATH)
	make -C libs/libft debug
	$(CC) $(CFLAGS) $(DFLAGS) $(LIB_DEBUG) $(HEADERS) $(SRCS_TEST_FINDFULLPATH) -o $(TESTDIR)/testfindfullpath

clean:
	make -C libs/libft clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C libs/libft fclean
	rm -rf $(NAME) $(DNAME)

re: fclean all

.PHONY: all, clean, fclean, re, debug
