/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:04:56 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/06 14:31:00 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

void	pipex(char **argv, char **envp);
void	ft_parent(int fd [2], char **argv, char **envp);
void	ft_free_tab(char **tab);
void	ft_child(int fd [2], char **argv, char **envp);
char	*ft_search_path(char **envp, char *cmd);
int		ft_msgerr(char *err);
#endif
