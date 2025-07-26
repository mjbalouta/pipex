/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:55:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/25 13:40:31 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_first_mid_cmd(t_comm *comm, t_args *args, int i, int *pipefd)
{
	char	**curr_comm;

	if (comm->in_fd == -1)
		exit_safely(ERROR, comm);
	if (i == 2)
		dup2(comm->in_fd, STDIN_FILENO);
	else
		dup2(comm->prev_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (comm->prev_fd != -1)
		close(comm->prev_fd);
	curr_comm = ft_split(args->av[i], ' ');
	if (!curr_comm[0] || write_full_path(args->envp, &args->av[i], comm) == -1
		|| execve(comm->full_path, curr_comm, args->envp) == -1)
	{
		free_list(curr_comm);
		exit_safely(0, comm);
	}
	free_list(curr_comm);
}

void	execute_last_cmd(t_comm *comm, t_args *args, int i, int cmd_count)
{
	char	**curr_comm;

	if (comm->pid[cmd_count] < 0)
		exit_safely(ERROR, comm);
	if (comm->pid[cmd_count] == 0)
	{
		if (comm->out_fd == -1)
			exit_safely(ERROR, comm);
		dup2(comm->prev_fd, STDIN_FILENO);
		dup2(comm->out_fd, STDOUT_FILENO);
		curr_comm = ft_split(args->av[i], ' ');
		if (!curr_comm[0]
			|| write_full_path(args->envp, &args->av[i], comm) == -1
			|| execve(comm->full_path, curr_comm, args->envp) == -1)
		{
			free_list(curr_comm);
			exit_safely(ERROR_COMM, comm);
		}
		free_list(curr_comm);
	}
}

int	pipex(t_comm *comm, t_args *args)
{
	int	pipefd[2];
	int	i;
	int	status;
	int	cmd_count;

	i = 1;
	cmd_count = 0;
	while (++i < (args->ac - 2))
	{
		if (pipe(pipefd) == -1)
			exit_safely(ERROR, comm);
		comm->pid[cmd_count] = fork();
		if (comm->pid[cmd_count] < 0)
			exit_safely(ERROR, comm);
		if (comm->pid[cmd_count++] == 0)
			execute_first_mid_cmd(comm, args, i, pipefd);
		comm->prev_fd = pipefd[0];
		close(pipefd[1]);
	}
	comm->pid[cmd_count] = fork();
	execute_last_cmd(comm, args, i, cmd_count);
	cmd_count++;
	close_fds(comm);
	status = wait_for_child(comm, cmd_count);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	t_comm	comm;
	t_args	args;
	int		status;

	if (ac < 5)
		return (ft_printf("Error.\n"));
	args.av = av;
	args.ac = ac;
	args.envp = envp;
	initialize_mem(&comm, &args);
	status = pipex(&comm, &args);
	free_mem(&comm);
	return (status);
}
