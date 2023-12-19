/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/12/19 17:48:00 by marschul          #+#    #+#             */
/*   Updated: 2023/12/19 18:30:50 by marschul         ###   ########.fr       */
=======
/*   Created: 2023/12/18 09:07:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2023/12/19 17:54:39 by ***REMOVED***            ###   ########.fr       */
>>>>>>> 7ea1d10ceac01b1993234cfa5dc9c80dce56f69e
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

// typedef struct s_tokens {
// 	char 	*token;
// 	bool	in_s_quotes;
// 	bool	in_d_quotes;
// 	bool	pipe;
// 	bool	red_left;
// 	bool	red_right;
// }	t_tokens;

typedef struct s_process {
	char 	*name;
	char 	**argv;
	bool	pipe;
	bool	red_left;
	bool	red_right;
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

typedef bool (*t_function_pointer)(char **argv);

// input_utils.c
char	*read_a_line(char *prompt);

// echo.c
bool	echo(char **argv);

// cd.c
bool	cd(char **argv);

// pwd.c
bool	pwd(void);

// export.c
bool	export_one_pair(char *env_pair);
void	free_old_env(char **old_env);
size_t	get_env_length(void);

// unset.c
bool	unset(char *variable_name);

// env.c
bool	env(void);
