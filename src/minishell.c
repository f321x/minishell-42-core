/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/11 17:29:39 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_exit_code(void)
{
	char	*argv[3];

	argv[0] = "export";
	argv[1] = "?=0";
	argv[2] = NULL;
	export(argv);
}

// static void debug_printing(t_pipe *task)
// {
// 	// printing parsed argvs
// 		for (size_t i = 0; i < task->p_amount; i++)
// 		{
// 			int in = 0;
// 			printf("argv:");
// 			while (task->processes[i].argv && task->processes[i].argv[in])
// 			{
// 				printf(" %s", task->processes[i].argv[in]);
// 				in++;
// 			}
// 			printf("\n");

// 			int io = 0;
// 			printf("\niofiles:\n");
// 			while (io < task->processes[i].io_amount)
// 			{
// 				printf("NAME: %s\n", task->processes[i].iofiles[io].name);
// 				switch (task->processes[i].iofiles[io].type) {
// 					case IN: printf("TYPE: INFILE\n"); break;
// 					case OUT: printf("TYPE: OUTFILE\n"); break;
// 					case APPEND: printf("TYPE: APPEND\n"); break;
// 					case HEREDOC: printf("TYPE: HEREDOC\n"); break;
// 					default: printf("TYPE: UNDEFINED!!!\n");}
// 				io++;
// 			}
// 		}
// 		printf("\n");
// }

// register signal handlers
// initializes exit codes
// reads a line, if it contains content it will be added to history
// read line will be parsed in struct and passed to exec part
// afterwards the parsed data will be freed.
int	main(void)
{
	t_pipe	task;
	char	*entered_line;

	register_signal_handlers();
	initialize_exit_code();
	while (1)
	{
		task.p_amount = 0;
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;
		if (!parsing_main(entered_line, &task))
		{
			free(entered_line);
			continue ;
		}
		free(entered_line);
		execute_line(&task);
	}
	return (0);
}

// some random tests:

// 1. **Simple commands:**
//     - `ls`
//     - `pwd`
//     - `echo Hello, World!`

// 2. **Pipes:**
//     - `ls | grep .txt`
//     - `cat file.txt | sort | uniq`

// 3. **Redirections:**
//     - `echo Hello, World! > file.txt`
//     - `cat < file.txt`
//     - `ls > file.txt 2>&1`

// 4. **Combination of pipes and redirections:**
//     - `cat file.txt | sort > sorted.txt`
//     - `grep 'pattern' file.txt | wc -l > count.txt`

// 5. **Background processes:**
//     - `sleep 10 &`
//     - `ls &`

// 6. **Command sequences:**
//     - `cd /tmp; ls`
//     - `mkdir test; cd test; touch file.txt`

// 7. **Command substitution:**
//     - `ls -l $(which bash)`
//     - `echo Today is $(date)`

// 8. **Variable assignment and usage:**
//     - `VAR="Hello, World!"; echo $VAR`
