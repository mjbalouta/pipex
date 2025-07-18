/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/18 19:17:25 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft-projects/get-next-line/get_next_line.h"
# include "../libft-projects/libft/libft.h"
# include "../libft-projects/printf/libftprintf.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_comm
{
	char	**command;
	char	*full_path;
	int		fd;
}				t_comm;

int		verify_path(char **envp, t_comm *comm);
char	*find_path_variable(char **envp);
int		handle_comm(char **av, t_comm *comm_in, t_comm *comm_out, char **envp);
void	pipex(t_comm *comm_in, t_comm *comm_out, char **envp);
void	execute_cmd_two(int *pipefd, t_comm *comm, char **envp);
void	execute_cmd_one(int *pipefd, t_comm *comm, char **envp);
void	free_mem(t_comm *comm);
void	free_list(char **list);

#endif