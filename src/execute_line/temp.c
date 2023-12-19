oid	execute_processes(pid_t *pid_array, t_pipe *pipe_struct, int (*fd_array)[2])
{
	size_t			n;
	int				pid;
	t_process		process;
	char			*program;
	size_t			i;
	char			**argv;
	extern char		**environ;

	n = pipe_struct->p_amount;
	i = 0;
	while (n > 1 && i < n - 1)
	{
		process = pipe_struct->processes[i];
		program = process.name;
		argv = process.argv;
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd_array[i][0], 0);
			if (i != n - 2)
				dup2(fd_array[i + 1][1], 1);
			close(fd_array[i][0]);
			close(fd_array[i][1]);
			execve(program, argv, environ);
		}
		else
		{
			pid_array[i] = pid;
			close(fd_array[i][0]);
			close(fd_array[i][1]);
			
		}
		i++;
	}
}