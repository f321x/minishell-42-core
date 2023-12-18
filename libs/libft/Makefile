# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 10:22:25 by ***REMOVED***             #+#    #+#              #
#    Updated: 2023/12/18 14:55:11 by ***REMOVED***            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Combination of libft, printf and get_next_line projects to one library

NAME = libft.a
DNAME = libft_debug.a
CC = cc
# CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3
HEADERS = -I./includes

SRCDIR	:= src
OBJDIR	:= objs

SRCS = ft_putstr_fd.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c \
ft_lstsize.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf.c ft_hex_printf.c \
ft_printargument.c ft_ptr_printf.c ft_putunsigned.c ft_functions2_bonus.c ft_utils_bonus.c ft_putchar_fd_pf.c \
ft_putstr_fd_pf.c ft_atoll.c

OBJS	:= $(addprefix $(OBJDIR)/, $(notdir ${SRCS:.c=.o}))
DOBJS   := $(addprefix $(OBJDIR)/, $(notdir ${SRCS:.c=.d.o}))

$(shell mkdir -p $(OBJDIR))

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR)/%.d.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(DFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

debug: $(DOBJS)
	ar rcs $(DNAME) $(DOBJS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME) $(DNAME)

re: fclean all

.PHONY: all, clean, fclean, re, debug
