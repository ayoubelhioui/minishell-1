/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:11:00 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/24 10:25:55 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
#define EXPANDING_H
#include "../../minishell.h"

char    *dollar_sign_found(t_data *data, char **env, char *saver, int *last_dollar_index);
char    *expanding(char *str, char **env);
void    expanding_helper(t_expanding *vars);
void    expanding_init(t_expanding *vars, char *str);
void    expanding_final_part(t_expanding *vars);
char    *expanding_join(char *s1, char *s2);
#endif