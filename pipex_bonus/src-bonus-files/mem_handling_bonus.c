/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:29:12 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 23:08:44 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void initialize_mem(t_comm *comm)
{
	comm->full_path = NULL;
	comm->in_fd = -1;
	comm->out_fd = -1;
	comm->prev_fd = -1;
}

void	free_mem(t_comm *comm)
{
	if (comm->full_path)
		free(comm->full_path);
	if (comm->in_fd != -1)
		close(comm->in_fd);
	if (comm->out_fd != -1)
		close(comm->in_fd);
	if (comm->prev_fd != -1)
		close(comm->in_fd);
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
