/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:38:43 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/05/18 16:25:05 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    replace_with_real_value(t_data *data, char *real_value, char *saver ,int dollar_sign_position)
{
    char *new_string;
    int whole_length;
    int i;
    int j;
    
    i = 0;
    j = 0;
    whole_length = ((ft_strlen(data->context) - ft_strlen(real_value)));
    new_string = malloc(sizeof(char) * ((ft_strlen(data->context) - ft_strlen(saver)) + ft_strlen(real_value)));
    ft_strcpy(new_string, data->context, 0, dollar_sign_position - 1);
    int k = ft_strlen(real_value);
    i = dollar_sign_position - 1;
    while (j < k)
    {
        new_string[i] = real_value[j];
        j++;
        i++;
    }
    new_string[i] = '\0';
    data->context = ft_strjoin(new_string, data->context + (dollar_sign_position + ft_strlen(saver)));
}

void remove_the_word(t_data *data, char *saver, int position)
{
    char    *new_string;
    int     length;

    length = (ft_strlen(data->context) - ft_strlen(saver) + 1);
    new_string = malloc(sizeof(char) * length);
    ft_strcpy(new_string, data->context, 0, position);
    new_string = ft_strjoin(new_string, data->context + position + ft_strlen(saver) + 1);
    data->context = new_string;
}

void dollar_sign(t_data *data, char **env)
{
    int i;
    char *saver;
    char *real_value;
    int counter;

    counter = 0;
    data->index++;
    i = 0;
    while (data->context[data->index])
    {
        if (!(ft_isalnum(data->context[data->index])) && (data->context[data->index] != UNDER_SCORE))
            break ;
        counter++;
        data->index+=1;
    }
    saver = malloc(sizeof(char) * (counter + 1));
    while (data->context[data->index - counter] && i < counter)
    {
        saver[i] = data->context[data->index - counter + i];
        i++;
    }
    saver[i] = '\0';
    real_value = search_in_env(saver, env);
    if (real_value)
       replace_with_real_value(data, real_value, saver, (data->index - counter));
    else
        remove_the_word(data, saver, data->index - counter - 1);
}

void    double_quotes(t_data *data, char **env, int is_double_quotes)
{
    int i;

    i = data->index;
    while (data->context[data->index])
    {
        if (data->context[data->index] == DOLLAR_SIGN)
            dollar_sign(data, env);
        data->index++;
    }
    data->index = i;
    if (is_double_quotes)
        replacing_space(data, DOUBLE_QUOTE);
}


int check_unclosed_quotes(char *context)
{
    int quote;
    int i;

    quote = 0;
    i = 0;
    while (context[i])
    {
        if (context[i] == DOUBLE_QUOTE)
        {
            if (quote == DOUBLE_QUOTE)
                quote = 0;
            else if (quote == 0)
                quote = DOUBLE_QUOTE;
        }
        else if (context[i] == SINGLE_QUOTE)
        {
            if (quote == SINGLE_QUOTE)
                quote = 0;
            else if (quote == 0)
                quote = SINGLE_QUOTE;
        }
        i++;
    }
    return (quote);
}