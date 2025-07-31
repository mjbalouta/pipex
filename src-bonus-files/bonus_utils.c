/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:56:33 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/31 10:20:13 by mjoao-fr         ###   ########.fr       */
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

void	check_if_executable(t_comm *comm, t_args *args, int i)
{
	if (write_full_path(args->envp, &args->av[i], comm) == -1 && verify_if_path(&args->av[i][0]) == 0)
	{
		ft_printf("%s : command not found", args->av[i]); //não imprime????
		exit(127);
	}
}

