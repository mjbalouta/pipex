/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/31 11:28:18 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	verify_if_path(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (-1);
		i++;
	}
	return (0);
}

int	write_full_path(char **envp, t_comm *comm)
{
	char	**path_list;
	int		i;
	char	*full_path;

	if (verify_if_path(comm->command[0]) == -1)
	{
		comm->full_path = ft_strdup(comm->command[0]);
		return (0);
	}
	path_list = create_path_list(envp);
	i = 0;
	while (path_list[i])
	{
		full_path = create_full_path(path_list[i], comm->command[0]);
		if (access(full_path, X_OK) == 0)
		{
			comm->full_path = full_path;
			free_list(path_list);
			return (0);
		}
		i++;
		free(full_path);
	}
	free_list(path_list);
	return (-1);
}

void	handle_comm(t_args *args, t_comm *comm_in, t_comm *comm_out)
{
	comm_in->command = ft_split(args->av[2], ' ');
	comm_out->command = ft_split(args->av[3], ' ');
	comm_in->full_path = NULL;
	comm_out->full_path = NULL;
}
