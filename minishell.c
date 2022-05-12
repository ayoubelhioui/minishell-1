/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:04:14 by marvin            #+#    #+#             */
/*   Updated: 2022/05/12 18:13:19 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    trim_all(char **data)
{
    int i;

    i = 0;
    while (data[i])
    {
        if (data[i][0] == '\'')
            data[i] = ft_strtrim(data[i], "'");
        else
            data[i] = ft_strtrim(data[i], "\"");
        i++;
    }
}

void    back_space(char *context)
{
    int i;

    i = 0;
    while (context[i])
    {
        if (context[i] == '\'')
        {
            i++;
            while (context[i] != '\'' && context[i])
            {
                if (context[i] == -1)
                    context[i] = ' ';
                i++;
            }
        }
        if (!context[i])
            break;
        i++;
    }
}

void    replacing(char *context, int *index, char quotes)
{
    *index+=1;
    while (context[*index] && context[*index] != quotes)
    {
        if (context[*index] == ' ')
            context[*index] = -1;
        *index+=1;
    }
}
void    search_in_env(char *data, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        
    }
}
void    dollar_sign(char *context, int *index, char **env)
{
    int i;
    char *saver;
    int counter;

    counter = 0;
    *index+=1;
    i = 0;
    while (context[*index] && context[*index] != ' ')
    {
        counter++;
        *index+=1; 
    }
    saver = malloc(sizeof(char) * (counter + 1));
    while (context[*index - counter + i] && context[*index - counter + i] != ' ' && context[*index - counter + i] != '\"')
    {
        saver[i] = context[*index - counter + i];
        i++;
    }
    saver[i] = '\0';
    
}
void    double_quotes(char *context, int *index, char **env)
{
    int i;

    i = *index;
    while (context[i])
    {
        if (context[i] == '$')
            dollar_sign(context, &i, env);
        i++;
    }
    replacing(context, index, '\"');
}

void     quotes_handling(char *context, char **env)
{
    char **data;
    int i;

    i = 0;
    while (context[i])
    {
        if (context[i] == '\'')
            replacing(context, &i, '\'');
        else if (context[i] == '$' || context[i] == '\"')
            double_quotes(context, &i, env);
        i++;
    }
    data = ft_split(context, ' ');
    i = 0;
    while (data[i])
        back_space(data[i++]);
    trim_all(data);
    i = 0;
    while (data[i])
        printf("%s\n", data[i++]);
}
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)env;
    (void)av;
    char *context;
	struct sigaction sa;
	// sa.sa_handler = &sig_handler;
	// sa.sa_flags =  SA_RESTART;
	sigaction (SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        context = readline("minishell : ");
		if (context == NULL)
			exit(1);
		if (builtcmd(context))
			
        add_history(context);
        quotes_handling(context, env);
        // pipe_handling(s);
        // break;
    }
}