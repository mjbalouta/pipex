/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:55:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/31 13:07:43 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_first_mid_cmd(t_comm *comm, t_args *args, int i, int *pipefd)
{
	char	**curr_comm;

	if (i == comm->start_index)
	{
		if (comm->in_fd == -1)
		{
			perror(args->av[1]);
			exit_safely(ERROR, comm);
		}
		dup2(comm->in_fd, STDIN_FILENO);
	}
	else
		dup2(comm->prev_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (comm->prev_fd != -1)
		close(comm->prev_fd);
	curr_comm = ft_split(args->av[i], ' ');
	if (!curr_comm)
		exit_safely(ERROR, comm);
	if (write_full_path(args->envp, &args->av[i], comm) == -1
		|| execve(comm->full_path, curr_comm, args->envp) == -1)
		return_error(0, curr_comm, comm);
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
		{
			perror(args->av[args->ac - 1]);
			exit_safely(ERROR, comm);
		}
		dup2(comm->prev_fd, STDIN_FILENO);
		dup2(comm->out_fd, STDOUT_FILENO);
		curr_comm = ft_split(args->av[i], ' ');
		if (!curr_comm)
			exit_safely(ERROR, comm);
		if (write_full_path(args->envp, &args->av[i], comm) == -1
			|| execve(comm->full_path, curr_comm, args->envp) == -1)
			return_error(ERROR_COMM, curr_comm, comm);
		free_list(curr_comm);
	}
}

int	pipex(t_comm *comm, t_args *args)
{
	int	pipefd[2];
	int	i;
	int	status;
	int	cmd_count;

	i = comm->start_index - 1;
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

void	register_heredoc_input(t_comm *comm, t_args *args)
{
	char	*line;
	int		pipefd[2];

	comm->start_index = 3;
	comm->limiter = args->av[2];
	if (pipe(pipefd) == -1)
		exit_safely(1, comm);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (line[ft_strlen(comm->limiter)] == '\n'
			&& ft_strncmp(line, comm->limiter, ft_strlen(comm->limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	get_next_line(-1);
	close(pipefd[1]);
	comm->in_fd = pipefd[0];
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
	if (initialize_mem(&comm, &args) == -1)
		return (perror(args.av[1]), 1);
	if (ft_strncmp(args.av[1], "here_doc", 9) == 0)
	{
		if (ac < 6)
			return (perror(args.av[1]), free_mem(&comm), 1);
		comm.out_fd = open(args.av[args.ac - 1], O_CREAT
				| O_WRONLY | O_APPEND, 0644);
		register_heredoc_input(&comm, &args);
	}
	else
		comm.out_fd = open(args.av[args.ac - 1], O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
	status = pipex(&comm, &args);
	free_mem(&comm);
	return (status);
}
