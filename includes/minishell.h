/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:48:00 by marschul          #+#    #+#             */
/*   Updated: 2023/12/20 16:49:29 by marschul         ###   ########.fr       */
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
#include <assert.h>
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
	t_function_pointer	inbuilt;
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

// parsing_main.c
bool	parse_line(char *entered_line, t_pipe *task);

int	execute_line(t_pipe *pipe_struct);