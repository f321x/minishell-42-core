#include "minishell.h"

void	test_findfullpath_1()
{
	t_process	process;
	bool		return_value;

	process.name = "/bin/ls";

	printf("find_full_path: Test absolute path\n");

	return_value = find_full_path(&process);

	assert(return_value == true && ft_strcmp(process.name, "/bin/ls") == 0);
}

void	test_findfullpath_2()
{
	t_process	process;
	bool		return_value;

	process.name = "ls";

	printf("find_full_path: Test path relative to a path in the PATH var\n");

	return_value = find_full_path(&process);

	assert(return_value == true && ft_strcmp(process.name, "/bin/ls") == 0);
}

void	test_findfullpath_3()
{
	t_process	process;
	bool		return_value;
	char		buffer[1000];
	char		*temp, *targetname;

	process.name = "testdummy";
	
	printf("find_full_path: Test path relative to cwd\n");

	getcwd(buffer, 1000);
	temp = ft_strjoin(buffer, "/");
	targetname = ft_strjoin(temp, "testdummy");
	open("testdummy", O_CREAT | O_WRONLY);
	return_value = find_full_path(&process);

	assert(return_value == true && ft_strcmp(process.name, targetname) == 0);
}

void	test_findfullpath_4()
{
	t_process	process;
	bool		return_value;

	process.name = "bogus";

	printf("find_full_path: Test path not relative to path in PATH var and not relative to cwd\n");

	return_value = find_full_path(&process);

	assert(return_value == true && ft_strcmp(process.name, "bogus") == 0);
}

int	main()
{
	test_findfullpath_1();
	test_findfullpath_2();
	test_findfullpath_3();
	test_findfullpath_4();
}
