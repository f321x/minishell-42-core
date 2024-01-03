#include "minishell.h"

void	set_basedir(char basedir[1000])
{
	getcwd(basedir, 1000);
}

void	test_cd_1()
{
	char	*argv[2];
	char	buffer[1000];

	argv[0] = "cd";
	argv[1] = NULL;
	
	printf("cd: Test without parameter\n");

	cd(argv);

	assert(ft_strcmp(getcwd(buffer, 1000), getenv("HOME")) == 0);
}

void	test_cd_2(char basedir[1000])
{
	char	*argv[3];
	char	buffer[1000];
	char	*targetdir;

	argv[0] = "cd";
	argv[1] = "src";
	argv[2] = NULL;
	
	printf("cd: Test with parameter. Change into subdirectory\n");

	targetdir  = ft_strjoin(basedir, "/src");
	chdir(basedir);
	cd(argv);

	assert(ft_strcmp(getcwd(buffer, 1000), targetdir) == 0);
}

void	test_cd_3()
{
	char	*argv[3];
	char	buffer[1000];

	argv[0] = "cd";
	argv[1] = "/Users";
	argv[2] = NULL;
	
	printf("cd: Test with parameter. Change into absolute path\n");

	cd(argv);

	assert(ft_strcmp(getcwd(buffer, 1000), "/Users") == 0);
}

void	test_cd_4(char basedir[1000])
{
	char	*argv[3];
	char	buffer[1000];
	bool	return_value;

	argv[0] = "cd";
	argv[1] = "bogus";
	argv[2] = NULL;
	
	printf("cd: Test with parameter. Non existent directory\n");

	write(2, "There should be an error message >>> ", 38);
	chdir(basedir);
	return_value = cd(argv);

	assert(return_value == false);
}

void	test_echo_1()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = NULL;

	printf("echo: Test without parameter, without n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_echo_2()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = "-n";
	argv[2] = NULL;

	printf("echo: Test without parameter, with n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_echo_3()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = "one";
	argv[2] = NULL;

	printf("echo: Test with one parameter, without n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_echo_4()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = "one";
	argv[2] = "two";
	argv[3] = "three";
	argv[4] = NULL;

	printf("echo: Test with 3 parameters, without n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_echo_5()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = "-n";
	argv[2] = "one";
	argv[3] = NULL;

	printf("echo: Test with one parameter, with n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_echo_6()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = "-n";
	argv[2] = "one";
	argv[3] = "two";
	argv[4] = "three";
	argv[5] = NULL;

	printf("echo: Test with 3 parameters, with n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_echo_7()
{
	char	*argv[6];

	argv[0] = "echo";
	argv[1] = "one";
	argv[2] = "-n";
	argv[3] = "two";
	argv[4] = NULL;

	printf("echo: Test with 2 parameters, one in the middle looking like the n flag\n");

	write(1, "output>", 7);
	echo(argv);
	write(1, "<end\n", 5);
}

void	test_env_1()
{
	char	*argv[2];

	argv[0] = "env";
	argv[1] = NULL;

	printf("env: Test without arguments\n");

	env(argv);

	write(1, "\n", 1);
}

void	test_env_2()
{
	char	*argv[3];
	bool	return_value;

	argv[0] = "env";
	argv[1] = "bogus";
	argv[2] = NULL;

	printf("env: Test with argument. Should return false.\n");

	write(1, "output>>>", 9);
	return_value = env(argv);

	assert(return_value == false);
}

void	test_exit_1()
{
	printf("exit: Test without argument\nShould exit with value 0.\n");

}

void	test_exit_2()
{
	printf("exit: Test with argument < 256\nShould exit with value.\n");
}

void	test_exit_3()
{
	printf("exit: Test with argument >= 256\nShould exit with value modulo 256.\n");
}

void	test_exit_4()
{
	printf("exit: Test with non numeric argument\nShould exit with exit code 255, but give an error message before.\n");
}

void	test_export_1()
{
	char	*argv[4];

	argv[0] = "export";
	argv[1] = NULL;

	printf("export: Test without arguments\nHow should our Minishell behave here?\n");

	export(argv);
}

void	test_export_2()
{
	char	*argv[4];

	argv[0] = "export";
	argv[1] = "a=a";
	argv[2] = NULL;

	printf("export: Test with 1 argument\n");

	export(argv);

	assert(ft_strcmp(getenv("a"), "a") == 0);
}

void	test_export_3()
{
	char	*argv[4];

	argv[0] = "export";
	argv[1] = "b=b";
	argv[2] = "c=c";
	argv[3] = NULL;

	printf("export: Test with 2 arguments\n");

	export(argv);

	assert(ft_strcmp(getenv("b"), "b") == 0);
	assert(ft_strcmp(getenv("c"), "c") == 0);
}

void	test_export_4()
{
	char	*argv[4];

	argv[0] = "export";
	argv[1] = "a=x";
	argv[2] = NULL;

	printf("export: Test with 1 argument that already existed\n");

	export(argv);

	assert(ft_strcmp(getenv("a"), "x") == 0);
}

void	test_export_5()
{
	char	*argv[4];

	argv[0] = "export";
	argv[1] = "dummy";
	argv[2] = NULL;

	printf("export: Test with invalid argument, that is a string without = in it\n");

	export(argv);

	assert(getenv("dummy") == NULL);
}

void	test_pwd_1(char	basedir[1000])
{
	char	*argv[3];
	char	buffer[1000];

	argv[0] = "pwd";
	argv[1] = NULL;

	printf("pwd: Test without argument\n");

	chdir(basedir);
	write(1, "output>>>", 9);
	pwd(argv);

	getcwd(buffer, 1000);
	assert(ft_strcmp(buffer, basedir) == 0);
}

void	test_pwd_2(char	basedir[1000])
{
	char	*argv[4];
	char	buffer[1000];

	argv[0] = "pwd";
	argv[1] = "bogus";
	argv[2] = "bogus";
	argv[3] = NULL;

	printf("pwd: Test with arguments\n");

	chdir(basedir);
	write(1, "output>>>", 9);
	pwd(argv);

	getcwd(buffer, 1000);
	assert(ft_strcmp(buffer, basedir) == 0);
}

void	test_unset_1()
{
	char	*argv[5];

	argv[0] = "unset";
	argv[1] = NULL;

	printf("unset: Test with no arguments\n");

	unset(argv);
	
	printf("Nothing should change\n");
}

void	test_unset_2()
{
	char	*argv[5];
	char	*export_argv[3];

	argv[0] = "unset";
	argv[1] = "a";
	argv[2] = NULL;
	export_argv[0] = "export";
	export_argv[1] = "a=a";
	export_argv[2] = NULL;

	printf("unset: Test with 1 argument\n");

	export(export_argv);
	unset(argv);

	assert(getenv("a") == NULL);
}

void	test_unset_3()
{
	char	*argv[5];
	char	*export_argv[4];

	argv[0] = "unset";
	argv[1] = "a";
	argv[2] = "b";
	argv[3] = NULL;
	export_argv[0] = "export";
	export_argv[1] = "a=a";
	export_argv[2] = "b=b";
	export_argv[3] = NULL;

	printf("unset: Test with 2 arguments\n");

	export(export_argv);
	unset(argv);

	assert(getenv("a") == NULL);
	assert(getenv("b") == NULL);
}

void	test_unset_4()
{
	char	*argv[5];

	argv[0] = "unset";
	argv[1] = "x";
	argv[4] = NULL;

	printf("unset: Test with non existent var\n");

	unset(argv);

	printf("Nothing should change\n");
}

void	test_unset_5()
{
	char	*argv[5];
	char	*export_argv[4];

	argv[0] = "unset";
	argv[1] = "a";
	argv[2] = "x";
	argv[2] = "b";
	argv[3] = NULL;
	export_argv[0] = "export";
	export_argv[1] = "a=a";
	export_argv[2] = "b=b";
	export_argv[3] = NULL;

	printf("unset: Test with 3 arguments, the middle one non existent\n");

	export(export_argv);
	unset(argv);

	assert(getenv("a") == NULL);
	assert(getenv("b") == NULL);
}

//******************

int	main()
{
	char	basedir[1000];

	set_basedir(basedir);
	test_cd_1();
	test_cd_2(basedir);
	test_cd_3();
	test_cd_4(basedir);

	write(1, "\n\n\n", 3);

	test_echo_1();
	test_echo_2();
	test_echo_3();
	test_echo_4();
	test_echo_5();
	test_echo_6();
	test_echo_7();

	write(1, "\n\n\n", 3);

	test_env_1();
	test_env_2();

	write(1, "\n\n\n", 3);

	test_exit_1();
	test_exit_2();
	test_exit_3();
	test_exit_4();

	write(1, "\n\n\n", 3);

	test_export_1();
	test_export_2();
	test_export_3();
	test_export_4();
	test_export_5();

	write(1, "\n\n\n", 3);

	test_pwd_1(basedir);
	test_pwd_2(basedir);

	write(1, "\n\n\n", 3);

	test_unset_1();
	test_unset_2();
	test_unset_3();
	test_unset_4();
	test_unset_5();
}