/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:07:50 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/25 16:28:51 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H
# include "../../minishell.h"
# include "../expanding/expanding.h"

int	here_doc_helper2(t_here_doc_vars *vars, char *limiter, char **env);
int	here_doc_helper(t_here_doc_vars *vars, char *limiter, char **env);
int	here_doc(char *limiter, char **env);
int	heredoc_searcher(char **splitted_data, \
t_returned_data *returned_data, char **env);
int	find_heredoc_position(char **s);
char	*expanding_here_doc(char *str, char **env);

#endif