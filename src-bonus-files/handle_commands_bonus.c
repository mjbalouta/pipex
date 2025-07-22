/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/22 12:09:31 by mjoao-fr         ###   ########.fr       */
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

int	write_full_path(char **envp, char *command, t_comm *comm)
{
	char	*env_path;
	char	**path_list;
	char	*path;
	char	*full_path;
	int		i;

	env_path = find_path_variable(envp);
	path_list = ft_split(env_path, ':');
	i = 0;
	while (path_list[i])
	{
		path = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(path, command[0]);
		free(path);
		if (verify_command(full_path) == -1)
		{
			free(full_path);
			free_list(path_list);
			return (-1);
		}
		comm->full_path = full_path;
		free_list(path_list);
		i++;
	}
	return (0);
}

int	verify_command(char *full_path)
{
	if (access(full_path, X_OK) == 0)
		return (0);
	return (-1);
}

int	handle_comm(t_args *args, t_comm *comm, char **envp)
{
	int		i;
	char	**curr_comm;

	i = 2;
	while (i < (args->ac - 1))
	{
		curr_comm = ft_split(args->av[i], ' ');
		if (i == 2)
			comm->first_command = curr_comm;
		else if (i == (args->ac - 2))
			comm->last_command = curr_comm;
		if (write_full_path(envp, curr_comm, comm) == -1)
		{
			if (comm->first_command)
				free_list(comm->first_command);
			if (comm->last_command)
				free_list(comm->last_command);
			free_list(curr_comm);
			return (-1);
		}
	}
	return (0);
}
