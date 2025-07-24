/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 18:20:20 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	write_full_path(char **envp, t_comm *comm)
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

void	handle_comm(t_args *args, t_comm *comm_in, t_comm *comm_out)
{
	comm_in->command = ft_split(args->av[2], ' ');
	comm_out->command = ft_split(args->av[3], ' ');
	comm_in->full_path = NULL;
	comm_out->full_path = NULL;
}
