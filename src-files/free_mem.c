/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:29:12 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 13:08:16 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_mem(t_comm *comm)
{
	if (comm->command)
		free_list(comm->command);
	if (comm->full_path)
		free(comm->full_path);
	if (comm->fd != -1)
		close(comm->fd);
}

void	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	list = NULL;
}

void	free_commands(t_comm *comm_in, t_comm *comm_out)
{
	free_mem(comm_in);
	free_mem(comm_out);
}
