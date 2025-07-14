/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/14 16:13:32 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft-projects/get-next-line/get_next_line.h"
# include "./libft-projects/libft/libft.h"
# include "./libft-projects/printf/libftprintf.h"

typedef struct s_command
{
	char	**command;
	char	*full_path;
}				t_command;

int		verify_path(char **envp, t_command *comm);
char	*find_path_variable(char **envp);
int		handle_commands(char **av, t_command *comm_in, t_command *comm_out, char **envp);
char	**find_command(char *av, t_command *comm);
void	free_mem(t_command *comm_in, t_command *comm_out);
void	free_path_list(char **path_list);


#endif