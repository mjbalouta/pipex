/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:29:12 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/11/12 14:09:02 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	initialize_mem(t_comm *comm, t_args *args)
{
	comm->start_index = 2;
	comm->in_fd = -1;
	comm->out_fd = -1;
	comm->prev_fd = -1;
	comm->full_path = NULL;
	comm->in_fd = open(args->av[1], O_RDONLY);
	comm->pid = ft_calloc((args->ac - 2), sizeof(pid_t));
	if (!comm->pid)
		exit(ERROR);
	return (0);
}

void	free_path(char *path)
{
	if (path)
	{
		free(path);
		path = NULL;
	}
}

void	free_mem(t_comm *comm)
{
	free_path(comm->full_path);
	close_fds(comm);
	if (comm->pid)
		free(comm->pid);
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

void	free_utils(char **path_list, char **comm_words)
{
	if (path_list)
		free_list(path_list);
	if (comm_words)
		free_list(comm_words);
}