/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:05:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/14 16:28:03 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	verify_path(char **envp, t_command *comm)
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
			free_path_list(path_list);
			return (0);
		}
		i++;
	}
	free_path_list(path_list);
	return (-1);
}

char	**find_command(char *av, t_command *comm)
{
	comm->command = ft_split(av, ' ');
	return (comm->command);
}

int	handle_commands(char **av, t_command *comm_in, t_command *comm_out, char **envp)
{
	comm_in->command = find_command(av[2], comm_in);
	comm_out->command = find_command(av[3], comm_out);
	if (verify_path(envp, comm_in) == -1 || verify_path(envp, comm_in) == -1)
		return (-1);
	return (0);
}