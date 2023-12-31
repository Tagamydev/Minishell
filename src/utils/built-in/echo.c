/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shujiang <shujiang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:51:34 by shujiang          #+#    #+#             */
/*   Updated: 2023/09/28 13:05:23 by shujiang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_only_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo_no_argv(char **input)
{
	if (input[1] == NULL)
	{
		printf("\n");
		return (1);
	}
	return (0);
}

void	ft_print_holder(char **input, int i)
{
	if (ft_strcmp(input[1], "-n") == 0)
		printf("%s", input[i]);
	else
		printf("%s\n", input[i]);
}

void	ft_echo(char **input)
{
	int	i;

	i = 1;
	if (ft_echo_no_argv(input))
		return ;
	while (input[i] && check_only_n(input[i]))
	{
		free(input[i]);
		input[i] = ft_strdup("-n");
		i++;
	}
	i = 1;
	while (ft_strcmp(input[i], "-n") == 0)
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
	ft_print_holder(input, i);
}
