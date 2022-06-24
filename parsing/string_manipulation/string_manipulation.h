/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:45:55 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 11:56:00 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STRING_MANIPULATION_H
# define STRING_MANIPULATION_H

#include "../../minishell.h"
void    in_a_quote(int *in_quote, int SINGLE_OR_DOUBLE);
int     get_new_string_length(char *context);
void    add_space_helper(char *context, t_add_space_vars *vars);
char    *add_space(char *context, int redirections_counter);
void    replacing_space(t_data *entered_data, char quote);
void    quotes_counter(char *context, int *start, char quote, int *counter);
void    remove_quotes_helper(char *context, t_remove_quotes_vars *vars);
char    *remove_quotes(char *context);
char    *get_new_context(t_data *entered_data);
int	    get_length(char **args);
#endif
