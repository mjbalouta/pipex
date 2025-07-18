/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/18 19:10:10 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd_one(int *pipefd, t_comm *comm, char **envp)
{
	dup2(comm->fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	execve(comm->full_path, comm->command, envp);
	perror("execve cmd1");
}

void	execute_cmd_two(int *pipefd, t_comm *comm, char **envp)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(comm->fd, STDOUT_FILENO);
	close(pipefd[1]);
	execve(comm->full_path, comm->command, envp);
	perror("execve cmd2");
}

void	pipex(t_comm *comm_in, t_comm *comm_out, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 < 0)
		perror("fork (pid1)");
	if (pid1 == 0)
		execute_cmd_one(pipefd, comm_in, envp);
	pid2 = fork();
	if (pid2 < 0)
		perror("fork (pid2)");
	if (pid2 == 0)
		execute_cmd_two(pipefd, comm_out, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_comm	comm_in;
	t_comm	comm_out;

	if (ac != 5)
		return (ft_printf("Error.\n"));
	comm_in.fd = open(av[1], O_RDONLY);
	if (comm_in.fd == -1)
		return (ft_printf("Error reading file.\n"));
	comm_out.fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (comm_out.fd == -1)
		return (ft_printf("Error creating the output file.\n"));
	if (handle_comm(av, &comm_in, &comm_out, envp) != 0)
		return (ft_printf("Can't execute command\n"));
	pipex(&comm_in, &comm_out, envp);
	free_mem(&comm_in);
	free_mem(&comm_out);
	close(comm_in.fd);
	close(comm_out.fd);
	return (0);
}
