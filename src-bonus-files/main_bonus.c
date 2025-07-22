/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:55:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/22 12:27:26 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_first_cmd(int *pipefd, t_comm *comm, char **envp, char *arg)
{
	dup2(comm->in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	comm->full_path = write_full_path(envp, arg, comm);
	execve(comm->full_path, comm->first_command, envp);
	perror("execve cmd1");
}
void	execute_middle_cmd(int *pipefd, t_comm *comm, char **envp, char *arg)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	comm->full_path = write_full_path(envp, arg, comm);
	execve(comm->full_path, comm->last_command, envp);
	perror("execve cmd2");
}

void	execute_last_cmd(int *pipefd, t_comm *comm, char **envp, char *arg)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(comm->out_fd, STDOUT_FILENO);
	close(pipefd[1]);
	comm->full_path = write_full_path(envp, arg, comm);
	execve(comm->full_path, comm->last_command, envp);
	perror("execve cmd2");
}

void	pipex(t_comm *comm, char **envp, t_args *args)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int		i;

	i = 1;
	pipe(pipefd);
	pid1 = fork();
	if (pid1 < 0)
		perror("fork (pid1)");
	if (pid1 == 0)
		execute_first_cmd(pipefd, comm, envp, args);
	while (i < (args->ac - 2))
	{
		pid3 = fork();
		if (pid3 < 0)
			perror("fork (pid3)");
		if (pid3 == 0)
			execute_middle_cmd(pipefd, comm, envp, args->av[i]);
		i++;
	}
	pid2 = fork();
	if (pid2 < 0)
		perror("fork (pid2)");
	if (pid2 == 0)
		execute_last_cmd(pipefd, comm, envp, args);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_comm	comm;
	t_args	args;

	if (ac != 5)
		return (ft_printf("Error.\n"));
	comm.in_fd = open(av[1], O_RDONLY);
	if (comm.in_fd == -1)
		return (ft_printf("Error reading file.\n"));
	comm.out_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (comm.out_fd == -1)
		return (ft_printf("Error creating the output file.\n"));
	args.av = av;
	args.ac = ac;
	if (handle_comm(&args, &comm, envp) != 0)
		return (ft_printf("Can't execute one of the commands.\n"));
	pipex(&comm, envp, &args);
	free_mem(&comm);
	close(comm.in_fd);
	close(comm.out_fd);
	return (0);
}
