/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 15:00:53 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd_one(int *pipefd, t_comm *comm_in, t_comm *comm_out, t_args *args)
{
	comm_in->fd = open(args->av[1], O_RDONLY);
	if (dup2(comm_in->fd, STDIN_FILENO) == -1)
	{
		free_commands(comm_in, comm_out);
		exit(ERROR);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		free_commands(comm_in, comm_out);
		exit(ERROR);
	}
	close(pipefd[0]);
	write_full_path(args->envp, comm_in);
	if (execve(comm_in->full_path, comm_in->command, args->envp) == -1)
	{
		free_commands(comm_in, comm_out);
		exit(0);
	}	
}

void	execute_cmd_two(int *pipefd, t_comm *comm_in, t_comm *comm_out, t_args *args)
{
	comm_out->fd = open(args->av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (comm_out->fd == -1)
	{
		free_commands(comm_in, comm_out);
		exit(ERROR);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		free_commands(comm_in, comm_out);
		exit(ERROR);
	}
	if (dup2(comm_out->fd, STDOUT_FILENO) == -1)
	{
		free_commands(comm_in, comm_out);
		exit(ERROR);
	}
	close(pipefd[1]);
	write_full_path(args->envp, comm_out);
	if (execve(comm_out->full_path, comm_out->command, args->envp) == -1)
	{
		free_commands(comm_in, comm_out);
		exit(ERROR_COMM);
	}
}

int	pipex(t_comm *comm_in, t_comm *comm_out, t_args *args)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	if (pid1 == 0)
		execute_cmd_one(pipefd, comm_in, comm_out, args);
	pid2 = fork();
	if (pid2 < 0)
		return (-1);
	if (pid2 == 0)
		execute_cmd_two(pipefd, comm_in, comm_out, args);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (status >> 8);
}

int	main(int ac, char **av, char **envp)
{
	t_comm	comm_out;
	t_comm	comm_in;
	int		status;
	t_args	args;

	comm_in.fd = -1;
	comm_out.fd = -1;
	args.av = av;
	args.ac = ac;
	args.envp = envp;
	if (args.ac != 5)
		return (ft_printf("Error.\n"));
	handle_comm(&args, &comm_in, &comm_out);
	status = pipex(&comm_in, &comm_out, &args);
	free_commands(&comm_in, &comm_out);
	return (status);
}
