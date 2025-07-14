/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/14 16:30:42 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int			infile;
	int			outfile;
	t_command	comm_in;
	t_command	comm_out;

	if (ac != 5)
		return (ft_printf("Error.\n"));
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	 	return (ft_printf("Error reading file.\n"));
	outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		return (ft_printf("Error creating the output file.\n"));
	if (handle_commands(av, &comm_in, &comm_out, envp) != 0)
		return (free_mem(&comm_in, &comm_out), ft_printf("Can't execute command\n"));
	close(infile);
	close(outfile);
	// free_mem(&comm_in, &comm_out);
	return (0);
}
