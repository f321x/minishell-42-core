/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:07:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/15 12:36:02 by marschul         ###   ########.fr       */
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
#define CWD_BUFFER_SIZE 10000
#define PROC_FIELD_BUFFER 1000
#define MAX_PROC_AMOUNT 1000
#define IOFILES_AMOUNT	100

typedef bool	(*t_function_pointer)(char **argv);

typedef enum e_ftypes {
	UNDEFINED,
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_ftypes;

typedef struct s_inoutfiles {
	char		*name;
	t_ftypes	type;
	bool		env_var;
}	t_inoutfiles;

typedef struct s_process {
	char				**argv;
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
bool	_exit_(char **argv, t_pipe *pipe_struct,
			int (*fd_array)[2], pid_t *pid_array);
bool	copy_old_env(char **old_env, char **new_env, size_t env_size);
bool	set_new_environ(char *new_pair, char **new_environ,
			char **old_environ, size_t size);
bool	set_false_argv_for_unset(char *key);

// parsing_main.c
bool	parsing_main(char *input, t_pipe *task);

// parsing_utils.c
void	init_parsing_data(t_parsing *data, t_pipe *task, char *input);
void	skip_whitespace(t_parsing *p);
bool	free_all_argvs(t_pipe *task);
// bool	add_to_argv(t_parsing *p);
bool	handle_pipe(t_parsing *p);

// parsing_functions.c
bool	parse_name(t_parsing *p);
bool	parse_delimiter(t_parsing *p);

// quote_parsing_new.c
bool	parse_single_quote(t_parsing *p, char *buffer, size_t *buffer_i);
bool	parse_double_quote(t_parsing *p, char *buffer, size_t *buffer_i);
void	fill_env_in_buffer(t_parsing *p, char *buffer, size_t *buffer_i);
bool	parse_remaining(t_parsing *p);
void	fill_env_buffer(char *buffer, t_parsing *p);

// parse_out_redirects.c
bool	parse_out_redirect(t_parsing *p);
bool	parse_in_redirect(t_parsing *p);

// parse_in_redirect.c
bool	parse_in_redirect(t_parsing *p);

// array_utils.c
char	**append_string(char **orig, char *str);

// string_utils.c
bool	ft_isdelimiter(char c);

// parsing_env_var.c
// bool	parse_env_assignment(t_parsing *p, char *buffer, size_t *buffer_i);
bool	fetch_env_var(char *buffer, char ***current_argv);

// env_var_utils.c
bool	fill_buffer(char *buffer, size_t buffer_s, t_parsing *p);
bool	parse_env_var(t_parsing *p);

// execute_line1.c
int		execute_line(t_pipe *pipe_struct);
int		cleanup(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array);

// execute_line2.c
bool	is_builtin(t_process *process);
bool	launch_builtin_in_parent(t_process *process);
pid_t	launch_process_in_parent(t_process *process);
void	execute_child_process(t_pipe *pipe_struct, int (*fd_array)[2], \
pid_t *pid_array, size_t i);

// heredoc.c
int		get_here_file(char *keyword, int true_stdin, int true_stdout);

// handle_iofiles.c
bool	handle_inoutfiles(t_process *process, int true_inout_fds[2]);

// handle_iofiles2.c
bool	get_tmp_name(char tmp_name[PATH_MAX]);

// find_full_path.c
bool	find_full_path(t_process *process);

//execute_line_utils.c
int		cleanup(t_pipe *pipe_struct, int (*fd_array)[2], pid_t *pid_array);
bool	create_pid_array(pid_t **pid_array, size_t p_amount);
bool	create_fd_array(int (*(*fd_array))[2], size_t n);
bool	create_pipes(int (*fd_array)[2], size_t n);

// exit_and_wait.c
bool	set_exit_value(int exit_value);
bool	wait_for_all(pid_t *pid_array, t_pipe *pipe_struct);
bool	is_exit(char *name);

// file-descriptors.c
void	close_all_fds(int (*fd_array)[2], size_t p_amount);
bool	close_last_fds(int (*fd_array)[2], size_t i);
void	restore_fds(int (*fd_array)[2], size_t p_amount);

// helper_functions.c
bool	error_wrapper(void);
bool	error_wrapper_bool(char *message);
bool	error_wrapper_int(char *message);
void	error_wrapper_exit(char *message);
void	free_vector(char **vector);

// signals.c
void	register_signal_handlers(void);
void	sigint_handler(int signum);

// gnl
char	*get_next_line(int fd);
