/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/11 15:29:27 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char *av)
{
	char *command;

	command = ft_split(av, ' ');

	return (command);
}

char	*verify_command(char **command)
{
	char	*path;
	char	*full_path;
	
	path = ft_calloc(ft_strlen(command[0]) + 1, sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, "/bin/", 5 + 1);
	full_path = ft_strjoin(path, command[0]);
	free(path);
	if (access(full_path, X_OK) != 0)
		return (NULL);
	//perceber melhor onde vou retornar o full_path
	return (full_path);
}

int	handle_commands(char **av)
{
	char	**comm_in;
	char	**comm_out;

	comm_in = find_command(av[2]);
	comm_out = find_command(av[3]);
	if (verify_command(comm_in) == NULL || verify_command(comm_out))
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*path_in;
	
	if (ac != 5)
		return (ft_printf("Error\n"));
	fd = open(av[1], O_RDONLY);
	if (fd != 0)
		return (ft_printf("Error reading file\n"));
	if (handle_commands != 0)
		return (ft_printf("Can't execute command\n"));
	close(fd);
}
