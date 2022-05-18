/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:04:14 by marvin            #+#    #+#             */
/*   Updated: 2022/05/18 18:16:21 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    back_space(char *context)
{
    int i;

    i = 0;
    while (context[i])
    {
        if (context[i] == -1)
            context[i] = SPACE;
        i++;
    }
}

void    replacing_space(t_data *entered_data, char quotes)
{
    entered_data->index++;
    while (entered_data->context[entered_data->index] && entered_data->context[entered_data->index] != quotes)
    {
        if (entered_data->context[entered_data->index] == ' ')
            (entered_data->context[entered_data->index]) = -1;
        entered_data->index++;
    }
}

char    *search_in_env(char *entered_data, char **env)
{
    int i;
    char **holder;

    if (ft_isdigit(entered_data[0]))
        return (entered_data + 1);
    if (!ft_isalnum(entered_data[0]) && entered_data[0] != UNDER_SCORE)
        return (ft_strjoin("$",entered_data));
    i = 0;
    holder = malloc(sizeof(char *) * 3);
    holder[2] = NULL;
    while (env[i])
    {
        holder = ft_split(env[i], EQUAL);
        if (ft_strcmp(holder[0], entered_data) == 0)
            return (holder[1]);
        i++;
    }
    return (NULL);
}

void    searching_for_dollar_sign(t_data *entered_data, char **env)
{
    int in_a_quote;

    in_a_quote = 0;
    entered_data->index = 0;
    while (entered_data->context[entered_data->index])
    {
        if (entered_data->context[entered_data->index] == DOUBLE_QUOTE)
        {
            if (in_a_quote == DOUBLE_QUOTE)
                in_a_quote = 0;
            else if (in_a_quote == 0)
                in_a_quote = DOUBLE_QUOTE;
        }
        else if (entered_data->context[entered_data->index] == SINGLE_QUOTE)
        {
            if (in_a_quote == SINGLE_QUOTE)
                in_a_quote = 0;
            else if (in_a_quote == 0)
                in_a_quote = SINGLE_QUOTE;
        }
        if ((entered_data->context[entered_data->index] == DOLLAR_SIGN) && (in_a_quote != SINGLE_QUOTE))
            dollar_sign(entered_data, env);
        entered_data->index++;
    }
}

int quotes_counter(char *context, int *start, char quote)
{
    int counter;

    counter = 0;
    *start+=1;
    while (context[*start] && context[*start] != quote)
    {
        *start+=1;
        counter++;
    }
    return (counter);
}

int allocation_length(char *context)
{
    int counter;
    int i;

    i = 0;
    counter = 0;
    while (context[i])
    {
        if (context[i] == DOUBLE_QUOTE)
            counter += quotes_counter(context, &i, DOUBLE_QUOTE);
        else if (context[i] == SINGLE_QUOTE)
            counter += quotes_counter(context, &i, SINGLE_QUOTE);
        else
            counter++;
        i++;
    }
    return (counter);
}

char    *remove_quotes(char *context, int new_string_length)
{
    char    *new_string;
    int      i;
    int      j;
    
    new_string = malloc(sizeof(char) * (new_string_length + 1));
    i = 0;
    j = 0;
    while (context[i])
    {
        if (context[i] == DOUBLE_QUOTE)
        {
            i++;
            while (context[i] && context[i] != DOUBLE_QUOTE)
                new_string[j++] = context[i++];
        }
        else if (context[i] == SINGLE_QUOTE)
        {
            i++;
            while (context[i] && context[i] != SINGLE_QUOTE)
                new_string[j++] = context[i++];
        }
        else
            new_string[j++] = context[i];
        i++;
    }
    new_string[j] = '\0';
    return (new_string);
}

void    quotes_final_touch(t_data *entered_data, char **env)
{
    int i;
    int length;

    i = 0;
    searching_for_dollar_sign(entered_data, env);
    entered_data->command_and_args = ft_split(entered_data->context, SPACE);
    while (entered_data->command_and_args[i])
    {
        length = allocation_length(entered_data->command_and_args[i]);
        entered_data->command_and_args[i] = remove_quotes(entered_data->command_and_args[i], length);
        back_space(entered_data->command_and_args[i]);
        i++;
    }
}

char	*get_command_path(char **env_variables, char *command)
{
	char	*full_path;
	char	**path;
	int		i;

	i = -1;
	while (env_variables[++i])
	{
		if (ft_strncmp(env_variables[i], "PATH", 4) == 0)
			break ;
	}
	path = ft_split(env_variables[i], ':');
	i = -1;
	while (path[++i])
	{
		full_path = ft_strjoin(ft_strjoin(path[i], "/"), command);
		if (access(full_path, F_OK) == 0)
			return (full_path);
	}
	return (command);
}

int get_length(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}
void    ft_strcpy(char *s, char *str,int start_position, int length)
{
    int i;

    i = 0;
    while (i < length)
    {
        s[i] = str[start_position];
        i++;
        start_position++;
    }
    s[i] = '\0';
}

void     get_cmd_args(t_data *entered_data, t_returned_data *returned_data, char **env)
{
    int i;
    int arguments_length;

    i = 0;
    entered_data->index = 0;
    while (entered_data->context[entered_data->index])
    {
        if (entered_data->context[entered_data->index] == SINGLE_QUOTE)
            replacing_space(entered_data, SINGLE_QUOTE);
        else if (entered_data->context[entered_data->index] == DOUBLE_QUOTE)
            replacing_space(entered_data, DOUBLE_QUOTE);
        entered_data->index++;
    }
    quotes_final_touch(entered_data, env);
    arguments_length = get_length(entered_data->command_and_args);
    returned_data->cmd_path = get_command_path(env, entered_data->command_and_args[0]);
    returned_data->args = malloc(sizeof(char *) * (arguments_length));
    while (i < arguments_length)
    {
        returned_data->args[i] = entered_data->command_and_args[i + 1];
        i++;
    }
}
// void    red_input(char *context)
// {}

void    red_output(char *context)
{
    int i;
    char    *file_name;

    i = 0;
    if (context[i] == SPACE)
        i++;
    while (context[i] && context[i] != SPACE)
        i++;
    file_name = ft_substr(context, 0, i);
}

void    determination(t_data *entered_data)
{
    int i;
    int which_one;

    i = 0;
    which_one = 0;
    while (entered_data->context[i])
    {
        if (entered_data->context[i] == '<')
        {
            which_one = RED_IN;
            if (entered_data->context[i + 1] == '<')
                which_one = HERE_DOC;
        }
        else if (entered_data->context[i] == '>')
        {
            which_one = RED_OUT;
            red_output(entered_data->context + i + 1);
            if (entered_data->context[i + 1] == '>')
                which_one = APPEND;
        }
        i++;
        // else
        // {}
    }
}

void    preparing(t_data *entered_data, char **env)
{
    // t_returned_data *returned_data;
    // int             i;
    (void)env;
    char            **splitted_data;
    // int             array_length;

    // i = 0;
    splitted_data = ft_split(entered_data->context, '|');
    determination(entered_data);
    // array_length = get_length(splitted_data);
    // returned_data = malloc(sizeof(t_returned_data) * (array_length));
    // while (i < array_length)
    // {
    //     entered_data->context = splitted_data[i];
    //     get_cmd_args(entered_data, &returned_data[i], env);
    //     i++;
    // }
    // i = 0;
    // int j = 0;
    // while (i < array_length)
    // {
    //     j = 0;
    //     printf("Command Is : %s\n", returned_data[i].cmd_path);
    //     while (returned_data[i].args[j])
    //         printf("Args Are : %s\n", returned_data[i].args[j++]);
    //     i++;
    // }
}

int main(int ac, char **av, char **env)
{
    (void)av;
    t_data entered_data;
	t_list	*env_l;
    
	if (ac != 1)
        exit (1);
	// sa.sa_handler = &sig_handler;
	// sa.sa_flags =  SA_RESTART;
	// sigaction (SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);
	create_list(env, &env_l);
    while (TRUE)
    {
        entered_data.context = readline("minishell : ");
		if (entered_data.context == NULL)
			exit(1);
		built_check(entered_data.context, &env_l);
        add_history(entered_data.context);
        if (check_unclosed_quotes(entered_data.context))
        {
            printf("Missing Quote!\n");
            continue ;
        }
        preparing(&entered_data, env);
        // quotes_handling(&entered_data, &returned_data, env);
    }
}