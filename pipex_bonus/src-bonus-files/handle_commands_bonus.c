/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/25 13:40:09 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**create_path_list(char **envp)
{
	char	*env_path;
	char	**path_list;
	int		i;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	path_list = ft_split(env_path, ':');
	return (path_list);
}

char	*create_full_path(char *path_list, char *comm_words)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin(path_list, "/");
	full_path = ft_strjoin(path, comm_words);
	free(path);
	return (full_path);
}

int	write_full_path(char **envp, char **command, t_comm *comm)
{
	char	**path_list;
	char	*full_path;
	int		i;
	char	**comm_words;

	if (!command || !command[0] || command[0][0] == '\0')
		return (-1);
	comm_words = ft_split(command[0], ' ');
	i = -1;
	path_list = create_path_list(envp);
	while (path_list[++i])
	{
		full_path = create_full_path(path_list[i], comm_words[0]);
		if (access(full_path, X_OK) == 0)
		{
			comm->full_path = full_path;
			free_utils(path_list, comm_words);
			return (0);
		}
		free(full_path);
	}
	free_utils(path_list, comm_words);
	return (-1);
}
