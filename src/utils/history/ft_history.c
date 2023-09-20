/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:21:28 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/20 19:00:12 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len_2_fill(int x, int new)
{
	static int	value = 0;

	if (x)
		value = new;
	return (value);
}

void	save_and_clear(void *content)
{
	char *str;
	static	int	i = 0;

	str = (char *)content;
	if (!str)
		return ;
	if (*str && (!((ft_get_history()) == STDIN_FILENO)))
	{
		if(i >= len_2_fill(0, 0))
		{
			ft_putstr_fd(str, ft_get_history());
			ft_putstr_fd("\n", ft_get_history());
		}
	}
	i++;
	ft_free((void **)&str);
	return ;
}

char	*ft_get_history_path(char **env)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp("HOME=", env[i], 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	str = *(env + i);
	str += 5;
	return (ft_strjoin(str, "/.minishell_history"));
}

void	ft_save_history_in_list(int fd, t_list **list)
{
	char	*str;

	str = get_next_line(fd);
	while(str)
	{
		str[ft_strlen(str) - 1] = '\0';
		ft_lstadd_back(list, ft_lstnew((void *)ft_strdup(str)));
		ft_free((void *)&str);
		str = get_next_line(fd);
	}
	return ;
}

int	fd_old_history_4_list(char **env, t_save_history *his)
{
	int		fd;
	char	*str2;

	str2 = ft_get_history_path(env);
	if (!str2)
		return (-1);
	fd = open(str2, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	ft_save_history_in_list(fd, &his->old_history);
	ft_lstadd_back(&his->old_history, his->history);
	close(fd);
	fd = open(str2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_free((void *)&str2);
	return (fd);
}

void	ft_save_history(void)
{
	t_save_history	his;

	his.old_history = NULL;
	his.history = (ft_get_static())->history;
	his.fd = ft_get_history();
	if (his.fd != -1 && his.fd != STDIN_FILENO)
		close(his.fd);
	his.env = list_to_matrix((ft_get_static())->env);
	//fd1
	his.fd = fd_old_history_4_list(his.env, &his);
	if (his.fd == -1)
	{
		return ;
	}
	his.len = ft_lstsize(his.old_history);
	his.len = his.len - 501;
	if(his.len < 0)
		his.len = 0;
	len_2_fill(1, his.len);
	ft_put_history(his.fd);
	ft_lstclear(&his.old_history, save_and_clear);
}