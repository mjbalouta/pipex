/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/22 12:10:50 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft-projects/get-next-line/get_next_line.h"
# include "../libft-projects/libft/libft.h"
# include "../libft-projects/printf/libftprintf.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_comm
{
	char	**first_command;
	char	**last_command;
	char	*full_path;
	int		in_fd;
	int		out_fd;
}				t_comm;

typedef struct s_args
{
	char	**av;
	int		ac;
}				t_args;


int		verify_path(char **envp, t_comm *comm);
char	*find_path_variable(char **envp);
int		handle_comm(t_args *args, t_comm *comm, char **envp);
void	pipex(t_comm *comm, char **envp, t_args *args);
void	execute_cmd_two(int *pipefd, t_comm *comm, char **envp);
void	execute_cmd_one(int *pipefd, t_comm *comm, char **envp);
void	free_mem(t_comm *comm);
void	free_list(char **list);
int		write_full_path(char **envp, char *command, t_comm *comm);

#endif