/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:38:43 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/02 13:28:49 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    replace_with_real_value(t_returned_data *data, char *real_value, char *saver, int dollar_position)
{
    char *new_string;
    int whole_length;
    int i;
    int j;
    
    i = 0;
    j = 0;
    whole_length = ((ft_strlen(data->args[data->str_idx]) - ft_strlen(real_value)));
    new_string = malloc(sizeof(char) * ((ft_strlen(data->args[data->str_idx]) - ft_strlen(saver)) + ft_strlen(real_value)));
    ft_strcpy(new_string, data->args[data->str_idx], 0, dollar_position - 1);
    int k = ft_strlen(real_value);
    i = dollar_position - 1;
    while (j < k)
    {
        new_string[i] = real_value[j];
        j++;
        i++;
    }
    new_string[i] = '\0';
    data->args[data->str_idx] = ft_strjoin(new_string, data->args[data->str_idx] + (dollar_position + ft_strlen(saver)));
}

void remove_the_word(t_returned_data *data, char *saver, int position)
{
    char    *new_string;
    int     length;

    length = (ft_strlen(data->args[data->str_idx]) - ft_strlen(saver) + 1);
    new_string = malloc(sizeof(char) * length);
    ft_strcpy(new_string, data->args[data->str_idx], 0, position);
    new_string = ft_strjoin(new_string, data->args[data->str_idx] + position + ft_strlen(saver) + 1);
    data->args[data->str_idx] = new_string;
}

void dollar_sign(t_returned_data *data, char **env, int dollar_position)
{
    int i;
    int j;
    char *saver;
    char *real_value;
    int counter;
    t_returned_data *temp;

    counter = 0;
    i = 0;
    temp = data;
    dollar_position++;
    while (data->args[data->str_idx][dollar_position])
    {
        if (!(ft_isalnum(data->args[data->str_idx][dollar_position])) && (data->args[data->str_idx][dollar_position] != UNDER_SCORE))
            break ;
        counter++;
        dollar_position++;
    }
    saver = malloc(sizeof(char) * (counter + 1));
    while (data->args[data->str_idx][dollar_position - counter] && i < counter)
    {
        saver[i] = data->args[data->str_idx][dollar_position - counter + i];
        i++;
    }
    saver[i] = '\0';
    real_value = search_in_env(saver, env);
    if (real_value)
       replace_with_real_value(data, real_value, saver, (dollar_position - counter));
    else
        remove_the_word(data, saver, dollar_position - counter - 1);
}

void    double_quotes(t_data *data, char **env, int is_double_quotes)
{
    int i;

    i = data->index;
    while (data->context[data->index])
    {
        // if (data->context[data->index] == DOLLAR_SIGN)
        //     dollar_sign(data, env);
        data->index++;
    }
    data->index = i;
    if (is_double_quotes)
        replacing_space(data, DOUBLE_QUOTE);
}


void    searching_for_dollar_sign(t_returned_data **data, char **env)
{
    int in_a_quote;
    int j;

    in_a_quote = 0;
    (*data)->str_idx = 0;
    while ((*data)->args[(*data)->str_idx])
    {
        j = 0;
        while ((*data)->args[(*data)->str_idx][j])
        {
            if ((*data)->args[(*data)->str_idx][j] == DOUBLE_QUOTE)
            {
                if (in_a_quote == DOUBLE_QUOTE)
                    in_a_quote = 0;
                else if (in_a_quote == 0)
                    in_a_quote = DOUBLE_QUOTE;
            }
            else if ((*data)->args[(*data)->str_idx][j] == SINGLE_QUOTE)
            {
                if (in_a_quote == SINGLE_QUOTE)
                    in_a_quote = 0;
                else if (in_a_quote == 0)
                    in_a_quote = SINGLE_QUOTE;
            }
            else if (((*data)->args[(*data)->str_idx][j] == DOLLAR_SIGN) && (in_a_quote != SINGLE_QUOTE))
                dollar_sign((*data), env, j);
            j++;
        }
        (*data)->str_idx+=1;
    }
}
