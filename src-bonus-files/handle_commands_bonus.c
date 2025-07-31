/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/31 16:51:07 by mjoao-fr         ###   ########.fr       */
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

int	verify_if_path(char **command, t_comm *comm)
{
	int	i;

	i = 0;
	if (comm->curr_comm[0])
		free_list(comm->curr_comm);
	while (command[0][i])
	{
		if (command[0][i] == '/')
		{
			comm->curr_comm = command;
			if (!comm->curr_comm)
				exit_safely(ERROR, comm);
			return (-1);
		}
		i++;
	}
	comm->curr_comm = command;
	if (!comm->curr_comm)
		exit_safely(ERROR, comm);
	return (0);
}

int	find_full_path(char *path, char *first_word_cmd, t_comm *comm)
{
	char	*full_path;

	full_path = create_full_path(path, first_word_cmd);
	if (access(full_path, X_OK) == 0)
	{
		comm->full_path = full_path;
		return (0);
	}
	free(full_path);
	return (-1);
}

int	write_full_path(char **envp, char **command, t_comm *comm)
{
	char	**path_list;
	int		i;
	char	**comm_words;

	free_path(comm->full_path);
	if (!command || !command[0] || command[0][0] == '\0')
		return (-1);
	if (verify_if_path(command, comm) == -1)
	{
		comm->full_path = ft_strdup(command[0]);
		return (0);
	}
	comm_words = ft_split(command[0], ' ');
	i = -1;
	path_list = create_path_list(envp);
	while (path_list[++i])
	{
		if (find_full_path(path_list[i], comm_words[0], comm) == 0)
			return (free_utils(path_list, comm_words), 0);
	}
	free_utils(path_list, comm_words);
	return (-1);
}
