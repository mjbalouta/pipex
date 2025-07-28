/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 18:24:32 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft-projects/get-next-line/get_next_line.h"
# include "../libft-projects/libft/libft.h"
# include "../libft-projects/printf/libftprintf.h"
# include <sys/types.h>
# include <sys/wait.h>

# define ERROR 1
# define ERROR_COMM 127

typedef struct s_comm
{
	char	**command;
	char	*full_path;
	int		fd;
}				t_comm;

typedef struct s_args
{
	char	**av;
	int		ac;
	char	**envp;
}				t_args;

int		write_full_path(char **envp, t_comm *comm);
char	*find_path_variable(char **envp);
void	handle_comm(t_args *args, t_comm *comm_in, t_comm *comm_out);
int		pipex(t_comm *comm_in, t_comm *comm_out, t_args *args);
void	ex_cm_one(int *pipefd, t_comm *comm_in, t_comm *comm_out, t_args *args);
void	ex_cm_two(int *pipefd, t_comm *comm_in, t_comm *comm_out, t_args *args);
void	free_mem(t_comm *comm);
void	free_list(char **list);
void	free_commands(t_comm *comm_in, t_comm *comm_out);

#endif