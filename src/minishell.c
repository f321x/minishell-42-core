/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:28:44 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/01/09 10:13:17 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_task(t_pipe *task)
{
	task->p_amount = 0;
	// task->input_file = NULL;
	// task->here_file = NULL;
	// task->output_file = NULL;
	// task->output_file_append = NULL;
}

void	initialize_exit_code(void)
{
	char	*argv[3];

	argv[0] = "export";
	argv[1] = "?=0";
	argv[2] = NULL;
	export(argv);
}

static void debug_printing(t_pipe *task)
{
	// printing parsed argvs
		for (size_t i = 0; i < task->p_amount; i++)
		{
			int in = 0;
			printf("argv:");
			while (task->processes[i].argv && task->processes[i].argv[in])
			{
				printf(" %s", task->processes[i].argv[in]);
				in++;
			}
			printf("\n");

			int io = 0;
			printf("\niofiles:\n");
			while (io < task->processes[i].io_amount)
			{
				printf("NAME: %s\n", task->processes[i].iofiles[io].name);
				switch (task->processes[i].iofiles[io].type) {
					case IN: printf("TYPE: INFILE\n"); break;
					case OUT: printf("TYPE: OUTFILE\n"); break;
					case APPEND: printf("TYPE: APPEND\n"); break;
					case HEREDOC: printf("TYPE: HEREDOC\n"); break;
					default: printf("TYPE: UNDEFINED!!!\n");}
				io++;
			}
		}
		printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe 	task;
	char	*entered_line;

	// register signal handlers
	register_signal_handlers();

	// initialize env var ? mit 0
	initialize_exit_code();

	while (1)
	{
		init_task(&task);
		task.p_amount = 0;

		// reading the input in a heap char array
		entered_line = read_a_line(SHELL_PROMPT);
		add_history(entered_line);
		if (!entered_line)
			continue ;

		// parsing the input for execution
		if (!parsing_main(entered_line, &task))
		{
			printf("parsing dead\n");
			free(entered_line);
			continue ;
		}

		// debug_printing(&task);

		// execution of parsed command
		execute_line(&task);

		// freeing for next use.
		// free_all_argvs(&task);  also done by execute line now
		free(entered_line);
		// printf("\n");
	}
	free_old_env(NULL);
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

// Remember to replace `file.txt` and `'pattern'` with actual file names and patterns that exist in your system.
