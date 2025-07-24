/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 11:25:55 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path_variable(char **envp)
{
	char	*env_path;
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
	return (env_path);
}

int	verify_command(char *full_path)
{
	if (access(full_path, X_OK) == 0)
		return (0);
	return (-1);
}

char	**create_path_list(char **envp)
{
	char	*env_path;
	char	**path_list;

	env_path = find_path_variable(envp);
	path_list = ft_split(env_path, ':');
	return (path_list);
}

int	write_full_path(char **envp, char **command, t_comm *comm)
{
	char	**path_list;
	char	*path;
	char	*full_path;
	int		i;
	char	**comm_words;

	comm_words = ft_split(command[0], ' ');
	i = 0;
	path_list = create_path_list(envp);
	while (path_list[i])
	{
		path = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(path, comm_words[0]);
		free(path);
		if (verify_command(full_path) == 0)
		{
			comm->full_path = full_path;
			free_utils(path_list, comm_words);
			return (0);
		}
		free(full_path);
		i++;
	}
	free_utils(path_list, comm_words);
	return (-1);
}

int	handle_comm(t_args *args, t_comm *comm)
{
	int		i;
	char	**curr_comm;

	i = 1;
	while (++i < (args->ac - 1))
	{
		curr_comm = ft_split(args->av[i], ' ');
		if (write_full_path(args->envp, curr_comm, comm) == -1)
		{
			free_list(curr_comm);
			return (-1);
		}
		if (comm->full_path)
			free(comm->full_path);
		comm->full_path = NULL;
		free_list(curr_comm);
	}
	return (0);
}
