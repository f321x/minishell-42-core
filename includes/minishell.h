/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:07:45 by fbock             #+#    #+#             */
/*   Updated: 2024/01/09 20:37:11 by marschul         ###   ########.fr       */
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
// #include <stdint.h>
#include "../libs/libft/includes/libft.h"

#define SHELL_PROMPT "minishell$ "
#define	CWD_BUFFER_SIZE 1000
#define	PROC_FIELD_BUFFER 1000
#define MAX_PROC_AMOUNT 1000
#define	IOFILES_AMOUNT	100

typedef bool (*t_function_pointer)(char **argv);

typedef enum {
	UNDEFINED,
	IN,
	OUT,
	APPEND,
	HEREDOC
}	e_ftypes;

typedef struct s_inoutfiles {
	char 		*name;  // heap, free!
	e_ftypes	type;
}	t_inoutfiles;

typedef struct s_process {
	char 				**argv;  // heap, free!
	t_inoutfiles		iofiles[IOFILES_AMOUNT];
	long				io_amount;
	t_function_pointer	builtin;
}	t_process;

typedef struct s_pipe {
	t_process	processes[MAX_PROC_AMOUNT];
	size_t		p_amount;
}	t_pipe;

typedef struct s_parsing {
	char	*u_input;
	size_t	inp_i;
	size_t	buffer_i;
	bool	new_proc;
	t_pipe	*task;
}	t_parsing;

// input_utils.c
char	*read_a_line(char *prompt);

// builtins
bool	echo(char **argv);
bool	cd(char **argv);
bool	pwd(char **argv);
bool	export_one_pair(char *env_pair);
void	free_old_env(char **old_env);
size_t	get_env_length(void);
bool	export(char **argv);
bool	unset(char **argv);
bool	env(char **argv);
bool	_exit_(char **argv, t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array);

// parsing_main.c
bool	parsing_main(char *input, t_pipe *task);

// parsing_utils.c
void	init_parsing_data(t_parsing *data, t_pipe *task, char *input);
void	skip_whitespace(t_parsing *p);
bool	free_all_argvs(t_pipe *task);
bool	add_to_argv(t_parsing *p);
bool	handle_pipe(t_parsing *p);

// parsing_functions.c
bool	parse_name(t_parsing *p);
bool	parse_delimiter(t_parsing *p);

// quote_parsing.c
bool	parse_single_quote(t_parsing *p);
bool	parse_double_quote(t_parsing *p);
void 	fill_env_in_buffer(t_parsing *p, char *buffer, size_t *buffer_i);

// parse_out_redirects.c
bool	parse_out_redirect(t_parsing *p);
bool	parse_in_redirect(t_parsing *p);
bool	parse_out_singlequotes(t_parsing *p, char *buffer, size_t *buff_i);
bool	parse_out_doublequotes(t_parsing *p, char *buffer, size_t *buff_i);

// parse_in_redirect.c
bool	parse_in_redirect(t_parsing *p);

// array_utils.c
char 	**append_string(char **orig, char *str);

// string_utils.c
bool	ft_isdelimiter(char c);

// parsing_env_var.c
void	fill_buffer(char *buffer, size_t buffer_s,
					char *string, size_t *str_index);
bool	parse_env_var(t_parsing *p);
void	parse_env_assignment(t_parsing *p, char *buffer, size_t *buffer_i);

// execute line
int		execute_line(t_pipe *pipe_struct);
int		cleanup(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array);

// helper_functions.c
bool	error_wrapper(void);
bool	error_wrapper_bool(char *message);
bool	error_wrapper_int(char *message);
void	free_vector(char **vector);

// signals.c
void	register_signal_handlers(void);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

// just for testing
bool	find_full_path(t_process *process);
