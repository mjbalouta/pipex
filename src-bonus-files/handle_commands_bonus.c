/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/18 20:03:56 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path_variable(char **envp)
{
	char	*env_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (env_path);
}

int	verify_path(char **envp, t_comm *comm)
{
	char	*env_path;
	char	**path_list;
	int		i;
	char	*path;
	char	*full_path;

	env_path = find_path_variable(envp);
	path_list = ft_split(env_path, ':');
	i = 0;
	while (path_list[i])
	{
		path = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(path, comm->command[0]);
		free(path);
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

int	handle_comm(char **av, t_comm *comm_in, t_comm *comm_out, char **envp)
{
	comm_in->command = ft_split(av[2], ' ');
	comm_out->command = ft_split(av[3], ' ');
	if (verify_path(envp, comm_in) == -1)
	{
		free_list(comm_in->command);
		free_list(comm_out->command);
		return (-1);
	}
	if (verify_path(envp, comm_out) == -1)
	{
		free_list(comm_in->command);
		free(comm_in->full_path);
		free_list(comm_out->command);
		return (-1);
	}
	return (0);
}
