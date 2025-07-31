/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/31 11:32:36 by mjoao-fr         ###   ########.fr       */
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
	pid_t	*pid;
	char	*limiter;
	int		start_index;
}				t_comm;

typedef struct s_args
{
	char	**av;
	int		ac;
	char	**envp;
}				t_args;

void	execute_first_mid_cmd(t_comm *comm, t_args *args, int i, int *pipefd);
void	execute_last_cmd(t_comm *comm, t_args *args, int i, int cmd_count);
int		pipex(t_comm *comm, t_args *args);
int		initialize_mem(t_comm *comm, t_args *args);
void	free_mem(t_comm *comm);
void	free_list(char **list);
void	free_utils(char **path_list, char **comm_words);
void	exit_safely(int error_type, t_comm *comm);
void	close_fds(t_comm *comm);
int		wait_for_child(t_comm *comm, int cmd_count);
char	**create_path_list(char **envp);
char	*create_full_path(char *path_list, char *comm_words);
int		write_full_path(char **envp, char **command, t_comm *comm);
void	free_path(char *path);
int		verify_if_path(char *command);
int		find_full_path(char *path, char *first_word_cmd, t_comm *comm);

#endif