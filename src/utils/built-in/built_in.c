/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shujiang <shujiang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:53:23 by shujiang          #+#    #+#             */
/*   Updated: 2023/09/01 20:26:29 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_cd(char *path)
{
	DIR *dir;

	if (!path)
	{
		chdir("$HOME");
		printf("Pls check the code. Here we need $ done\n");
		return ;
	}
	dir = opendir(path);
	if (dir)
	{
		if (access(path, X_OK) == -1)
		{
			printf("minishell: cd: %s: Permission denied\n", path);
			ft_put_error(1);
		}
		else
			chdir(path);
		closedir(dir);
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		ft_put_error(1);
	}
}

void ft_pwd(void)
{
	char buf[4096];

	printf("%s\n", getcwd(buf, sizeof(buf)));
}

void ft_echo(char    **input)
{
	int i;

	i = 1;
	if (input[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(input[i], "-n") == 0)
	{
		i++;
		if (!input[i])
			return ;		
	}
	while (input[i] && input[i + 1])
	{
		printf("%s ", input[i]);
		i++;
	}
	if (ft_strcmp(input[1], "-n") == 0)
		printf("%s", input[i]);
	else
		printf("%s\n", input[i]);
}

void ft_exit(char    **input)
{
	printf("exit\n");
	if (input[1] != NULL)
	{
		printf("minishell: exit: %s: numeric argument required\n", input[1]);
		ft_put_error(255);
	}
	ft_free_input(input);
	if (!ft_get_proccess())
		printf("yeah closing!!\n");
		//ft_save_history(ft_get_history());
	exit (0);
}

int	ft_built_in(char **input)
{
	if (input && ft_strcmp(input[0], "echo") == 0)
		ft_echo (input);
	else if (ft_strcmp(input[0], "cd") == 0)
		ft_cd(input[1]);
	else if (ft_strcmp(input[0], "pwd") == 0)
		ft_pwd ();
	else if (ft_strcmp(input[0], "export") == 0)
		ft_export (input);
	else if (ft_strcmp(input[0], "unset") == 0)
		ft_unset (input);
	else if (ft_strcmp(input[0], "env") == 0)
		ft_env (input);
	else if (ft_strcmp(input[0], "exit") == 0)
		ft_exit (input);  
	else
		return (false);
	return (true);
}

int	ft_excuter(char **input, char **env)
{
	t_bool	built_in;
	int	pid;
	int status;
	
	pid = 0;
	status = 0;
	
	built_in = ft_built_in(input);
	if (built_in == false)
	{
		
		flag = 1;
		pid = fork_with_error_check();
		if (pid == 0)
			execve_with_error_check(input, env);
		waitpid(-1, &status, 0);
		ft_free_split_2(&input);
		return (WEXITSTATUS(status));
	}
	else
	{
		ft_free_split_2(&input);
		return (errno);
	}
}