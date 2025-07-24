/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:55:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 22:23:58 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_first_mid_cmd(t_comm *comm, t_args *args, int i, int *pipefd)
{
	pid_t	pid1;
	char	**curr_comm;

	pid1 = fork();
	if (pid1 < 0)
		perror("fork (pid1)");
	if (pid1 == 0)
	{
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
			free_mem(comm);
			exit(0);
		}
		free_list(curr_comm);
	}
}

void	execute_last_cmd(t_comm *comm, t_args *args, int i)
{
	char	**curr_comm;

	dup2(comm->prev_fd, STDIN_FILENO);
	dup2(comm->out_fd, STDOUT_FILENO);
	write_full_path(args->envp, &args->av[i], comm);
	curr_comm = ft_split(args->av[i], ' ');
	if (!curr_comm[0] || write_full_path(args->envp, &args->av[i], comm) == -1
		|| execve(comm->full_path, curr_comm, args->envp) == -1)
	{
		free_list(curr_comm);
		free_mem(comm);
		exit(ERROR_COMM);
	}
	free_list(curr_comm);
}

int	pipex(t_comm *comm, t_args *args)
{
	int		pipefd[2];
	pid_t	pid2;
	int		i;
	int		status;

	i = 1;
	while (++i < (args->ac - 2))
	{
		if (pipe(pipefd) == -1)
			exit(ERROR);
		execute_first_mid_cmd(comm, args, i, pipefd);
		comm->prev_fd = pipefd[0];
		close(pipefd[1]);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit(ERROR);
	if (pid2 == 0)
		execute_last_cmd(comm, args, i);
	close(comm->prev_fd);
	close(pipefd[0]);
	while (waitpid(-1, &status, 0) > 0)
		;
	return (status >> 8);
}

int	main(int ac, char **av, char **envp)
{
	t_comm	comm;
	t_args	args;

	if (ac < 5)
		return (ft_printf("Error.\n"));
	comm.in_fd = open(av[1], O_RDONLY);
	comm.out_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	args.av = av;
	args.ac = ac;
	args.envp = envp;
	comm.prev_fd = -1;
	// handle_comm(&args, &comm);
	pipex(&comm, &args);
	free_mem(&comm);
	close(comm.in_fd);
	close(comm.out_fd);
	return (0);
}
