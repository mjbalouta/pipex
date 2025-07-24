/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/24 23:09:10 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft-projects/get-next-line/get_next_line.h"
# include "../libft-projects/libft/libft.h"
# include "../libft-projects/printf/libftprintf.h"
# include <sys/types.h>
# include <sys/wait.h>

# define ERROR 1
# define ERROR_COMM 127

typedef struct s_comm
{
	char	*full_path;
	int		in_fd;
	int		out_fd;
	int		prev_fd;
}				t_comm;

typedef struct s_args
{
	char	**av;
	int		ac;
	char	**envp;
}				t_args;

void	execute_first_mid_cmd(t_comm *comm, t_args *args, int i, int *pipefd);
void	execute_last_cmd(t_comm *comm, t_args *args, int i);
int		pipex(t_comm *comm, t_args *args);
char	*find_path_variable(char **envp);
int		write_full_path(char **envp, char **command, t_comm *comm);
int		verify_command(char *full_path);
int		handle_comm(t_args *args, t_comm *comm);
void	free_mem(t_comm *comm);
void	free_list(char **list);
void	free_utils(char **path_list, char **comm_words);
void 	initialize_mem(t_comm *comm);

#endif