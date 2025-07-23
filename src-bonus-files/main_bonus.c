/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:55:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/23 16:27:53 by mjoao-fr         ###   ########.fr       */
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
		write_full_path(args->envp, &args->av[i], comm);
		curr_comm = ft_split(args->av[i], ' ');
		execve(comm->full_path, curr_comm, args->envp);
		perror("execve cmd");
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
	execve(comm->full_path, curr_comm, args->envp);
	perror("execve last cmd");
	free_list(curr_comm);
}

void	pipex(t_comm *comm, t_args *args)
{
	int		pipefd[2];
	pid_t	pid2;
	int		i;

	i = 2;
	comm->prev_fd = -1;
	while (i < (args->ac - 2))
	{
		pipe(pipefd);
		execute_first_mid_cmd(comm, args, i, pipefd);
		if (comm->prev_fd != -1)
			close(comm->prev_fd);
		comm->prev_fd = pipefd[0];
		close(pipefd[1]);
		i++;
	}
	pid2 = fork();
	if (pid2 < 0)
		perror("fork (pid2)");
	if (pid2 == 0)
		execute_last_cmd(comm, args, i);
	close(comm->prev_fd);
	close(pipefd[0]);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

int	main(int ac, char **av, char **envp)
{
	t_comm	comm;
	t_args	args;

	if (ac < 5)
		return (ft_printf("Error.\n"));
	comm.in_fd = open(av[1], O_RDONLY);
	if (comm.in_fd == -1)
		return (ft_printf("Error reading file.\n"));
	comm.out_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (comm.out_fd == -1)
		return (ft_printf("Error creating the output file.\n"));
	args.av = av;
	args.ac = ac;
	args.envp = envp;
	if (handle_comm(&args, &comm) != 0)
		return (ft_printf("Can't execute one of the commands.\n"));
	pipex(&comm, &args);
	free_mem(&comm);
	close(comm.in_fd);
	close(comm.out_fd);
	return (0);
}
