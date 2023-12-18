/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:07:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/18 17:31:36 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <termios.h>
#include "libft.h"

#define SHELL_PROMPT "minishell$"
#define	CWD_BUFFER_SIZE 1000

typedef struct s_process {
	char 	*name;
	char 	**argv;
	char 	**env;
}	t_process;

typedef struct s_pipe {
	t_process	*processes;
	size_t		p_amount;
	char 		*input_file;
	char		*output_file;
}	t_pipe;

// input_utils.c
char	*read_a_line(char *prompt);

// echo.c
bool	echo(const char *after_echo, bool n_flag);

// cd.c
bool	cd(const char *entered_path_arg);

// pwd.c
bool	pwd(void);

// export.c
bool	export(char *env_pair);
