/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:56:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/07 10:31:34 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}

char	*ft_search_path(char **envp, char *cmd)
{
	char	**paths;
	char	*command;

	if (access(cmd, 0) == 0)
		return (cmd);
	if (!envp || !(*envp))
		return (NULL);
	while (envp && *envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!(*envp) || ft_strncmp("PATH=", *envp, 5))
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	command = ft_check_path(paths, cmd);
	ft_free_tab(paths);
	if (!command)
		return (NULL);
	return (command);
}

void	ft_child(int fd[2], char **argv, char **envp)
{
	char	**command;
	char	*path;
	int		f1;

	if (close(fd[0]))
		ft_msgerr("Close");
	f1 = open(argv[1], O_RDONLY);
	if (!f1)
		ft_msgerr("Infile");
	if (dup2(f1, STDIN_FILENO) == -1)
		return ;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return ;
	command = ft_split(argv[2], ' ');
	path = ft_search_path(envp, command[0]);
	if (!path)
	{
		ft_free_tab(command);
		perror("pipex");
		exit(127);
	}
	execve(path, command, envp);
	free(path);
	ft_free_tab(command);
}

void	ft_parent(int fd[2], char **argv, char **envp)
{
	char	**command;
	char	*path;
	int		f2;

	if (close(fd[1]))
		ft_msgerr("Close");
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (dup2(f2, STDOUT_FILENO) == -1)
		return ;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return ;
	command = ft_split(argv[3], ' ');
	path = ft_search_path(envp, command[0]);
	if (!path)
	{
		perror("pipex");
		ft_free_tab(command);
		exit(127);
	}
	if (execve(path, command, envp) == -1)
		perror("exceve");
	free(path);
	ft_free_tab(command);
}
