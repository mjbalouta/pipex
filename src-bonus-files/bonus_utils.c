/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:56:33 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/31 11:33:06 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_safely(int error_type, t_comm *comm)
{
	free_mem(comm);
	exit(error_type);
}

void	close_fds(t_comm *comm)
{
	if (comm->in_fd != -1)
		close(comm->in_fd);
	if (comm->out_fd != -1)
		close(comm->out_fd);
	if (comm->prev_fd != -1)
		close(comm->prev_fd);
}

int	wait_for_child(t_comm *comm, int cmd_count)
{
	int	last_status;
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(comm->pid[i], &status, 0);
		last_status = status;
		i++;
	}
	return (last_status >> 8);
}
