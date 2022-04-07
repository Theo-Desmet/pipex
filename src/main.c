/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:03:36 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/06 15:54:26 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (1);
	pipex(argv, envp);
	return (0);
}

void	pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_msgerr("Pipe");
	pid = fork();
	if (pid == -1)
		ft_msgerr("Fork");
	if (!pid)
		ft_child(fd, argv, envp);
	else
		ft_parent(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}
