/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:29:12 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/14 16:13:06 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_mem(t_command *comm_in, t_command *comm_out)
{
	if (comm_in->command)
		free(comm_in->command);
	if (comm_in->full_path)
		free(comm_in->full_path);
	if (comm_out->command)
		free(comm_out->command);
	if (comm_out->full_path)
		free(comm_out->full_path);
}

void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
	path_list = NULL;
}