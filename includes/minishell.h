/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:07:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/20 17:52:49 by ***REMOVED***            ###   ########.fr       */
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
#include "../libs/libft/includes/libft.h"

#define SHELL_PROMPT "minishell$ "
#define	CWD_BUFFER_SIZE 1000
#define	PROC_FIELD_BUFFER 1000

// typedef struct s_tokens {
// 	char 	*token;
// 	bool	in_s_quotes;
// 	bool	in_d_quotes;
// 	bool	pipe;
// 	bool	red_left;
// 	bool	red_right;
// }	t_tokens;

typedef bool (*t_function_pointer)(char **argv);

typedef struct s_process {
	char 	*name;
	char 	**argv;
	// bool	pipe;
	// bool	red_left;
	// bool	red_right;
	// char 	**env;
}	t_process;

typedef struct s_pipe {
	t_process	processes[1000];
	size_t		p_amount;
	char 		*input_file;
	char		*here_file;
	char		*output_file;
	char		*output_file_append;
}	t_pipe;

// input_utils.c
char	*read_a_line(char *prompt);

// echo.c
bool	echo(char **argv);

// cd.c
bool	cd(char **argv);

// pwd.c
bool	pwd(char **argv);

// export.c
bool	export_one_pair(char *env_pair);
void	free_old_env(char **old_env);
size_t	get_env_length(void);
bool	export(char **argv);

// unset.c
bool	unset(char **argv);

// env.c
bool	env(char **argv);

// parsing.c
bool	parse_line(char *entered_line, t_pipe *task);

// parsing_utils.c
char 	**append_string(char **orig, char *str);
bool	ft_isdelimiter(char c);
void	parse_placeholder(char *entered_line, size_t *line_i, size_t *buf_i, char *argv_buf);
