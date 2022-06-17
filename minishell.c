


#include "minishell.h"

void    in_a_quote(int *in_quote, int SINGLE_OR_DOUBLE)
{
    if (*in_quote == SINGLE_OR_DOUBLE)
        *in_quote = 0;
    else if (*in_quote == 0)
        *in_quote = SINGLE_OR_DOUBLE;
}

int check_unclosed_quotes(char *context)
{
    int in_quote;
    int i;

    in_quote = 0;
    i = 0;
    while (context[i])
    {
        if (context[i] == DOUBLE_QUOTE)
            in_a_quote(&in_quote, DOUBLE_QUOTE);
        else if (context[i] == SINGLE_QUOTE)
            in_a_quote(&in_quote, SINGLE_QUOTE);
        i++;
    }
    return (in_quote);
}

int error_handling_helper(t_error_handling_vars *vars, char *context)
{
    if (context[vars->i] == RED_INPUT && vars->in_quote == 0)
    {
        vars->i++;
        if (context[vars->i] == RED_OUTPUT || context[vars->i] == '\0')
            return (TRUE);
        if(context[vars->i] == RED_INPUT)
        {
            vars->i++;
            if (context[vars->i] == '\0' || context[vars->i] == RED_INPUT || context[vars->i] == RED_OUTPUT)
                return (TRUE);
        }
    }
    else if (context[vars->i] == RED_OUTPUT && vars->in_quote == 0)
    {
        vars->i++;
        if (context[vars->i] == RED_INPUT || context[vars->i] == '\0')
            return (TRUE);
        if(context[vars->i] == RED_OUTPUT)
        {
            vars->i++;
            if (context[vars->i] == '\0' || context[vars->i] == RED_OUTPUT || context[vars->i] == RED_INPUT)
                return (TRUE);
        }
    }
    return (FALSE);
}

int error_handling(char *context)
{
    t_error_handling_vars vars;

    vars.i = 0;
    vars.in_quote = 0;
    if (check_unclosed_quotes(context))
        return (TRUE);
    while (context[vars.i])
    {
        if (context[vars.i] == DOUBLE_QUOTE)
            in_a_quote(&vars.in_quote, DOUBLE_QUOTE);
        else if (context[vars.i] == SINGLE_QUOTE)
            in_a_quote(&vars.in_quote, SINGLE_QUOTE);
        if (context[vars.i] == PIPE && vars.in_quote == 0)
        {
            vars.i++;
            if (context[vars.i] == PIPE || context[vars.i] == '\0')
                return (TRUE);
        }
        else if (error_handling_helper(&vars, context))
            return (TRUE);
        if (context[vars.i] == '\0')
            return (FALSE);            
        vars.i++;
    }
    return (FALSE);
}
void    back_space(char *context)
{
    int i;

    i = 0;
    while (context[i])
    {
        if (context[i] == -1)
            context[i] = SPACE;
        else if (context[i] == -2)
            context[i] = PIPE;
        i++;
    }
}

void    replacing_space(t_data *entered_data, char quote)
{
    entered_data->index++;
    while (entered_data->context[entered_data->index] && entered_data->context[entered_data->index] != quote)
    {
        if (entered_data->context[entered_data->index] == ' ')
            entered_data->context[entered_data->index] = -1;
        else if (entered_data->context[entered_data->index] == PIPE)
            entered_data->context[entered_data->index] = -2;
        entered_data->index++;
    }
}

void    quotes_counter(char *context, int *start, char quote, int *counter)
{
    *start+=1;
    while (context[*start] && context[*start] != quote)
    {
        *start+=1;
        *counter+=1;
    }
}

int get_new_string_length(char *context)
{
    int inside_quotes_counter;
    int i;

    i = 0;
    inside_quotes_counter = 0;
    while (context[i])
    {
        if (context[i] == DOUBLE_QUOTE)
            quotes_counter(context, &i, DOUBLE_QUOTE, &inside_quotes_counter);
        else if (context[i] == SINGLE_QUOTE)
            quotes_counter(context, &i, SINGLE_QUOTE, &inside_quotes_counter);
        else
            inside_quotes_counter++;
        i++;
    }
    return (inside_quotes_counter);
}

char    *remove_quotes_helper(char *context, t_remove_quotes_vars *vars)
{
    while (context[vars->i])
    {
        if (context[vars->i] == DOUBLE_QUOTE)
        {
            vars->i++;
            while (context[vars->i] && context[vars->i] != DOUBLE_QUOTE)
                vars->new_string[vars->j++] = context[vars->i++];
        }
        else if (context[vars->i] == SINGLE_QUOTE)
        {
            vars->i++;
            while (context[vars->i] && context[vars->i] != SINGLE_QUOTE)
                vars->new_string[vars->j++] = context[vars->i++];
        }
        else
            vars->new_string[vars->j++] = context[vars->i];
        vars->i++;
    }
    vars->new_string[vars->j] = '\0';
    return (vars->new_string);
}

char    *remove_quotes(char *context)
{
    if (!context)
        return (NULL);
    t_remove_quotes_vars vars;
    char *returned;

    vars.new_string_length = get_new_string_length(context);
    vars.new_string = malloc(sizeof(char) * (vars.new_string_length + 1));
    vars.i = 0;
    vars.j = 0;
    return (remove_quotes_helper(context, &vars));
}


char	*get_command_path(char **env_variables, char *command)
{
	char	*full_path;
	char	**path;
    char    *temp;
    char    *temp1;
	int		i;

	i = -1;
	while (env_variables[++i])
	{
		if (ft_strncmp(env_variables[i], "PATH", 4) == 0)
			break ;
        if  (env_variables[i + 1] == NULL)
            return (NULL);
	}
	path = ft_split(env_variables[i], ':');
	i = -1;
    temp = remove_quotes(command);
	while (path[++i])
	{
        temp1 = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp1, temp);
		if (access(full_path, F_OK) == 0)
        {
            free (temp);
            free (temp1);
            ft_free(path);
			return (full_path);
        }
        free(temp1);
        free (full_path);
	}
    ft_free(path);
	return (temp);
}

int	get_length(char **args)
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
int get_args_length(char **data)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (data[i])
    {
        if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], ">"))
        {
            i++;
            counter+=2;
            if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], ">"))
            {
                i++;
                counter++;
            }
        }
        i++;
    }
    return (counter);
}

int redirection_counter(t_list *splitted_data, char redirection)
{
    int i;
    int counter;
    t_list *temp;

    i = 0;
    counter = 0;
    temp = splitted_data;
    while (temp)
    {
        if (((ft_strlen(temp->content)) == 1) && (temp->content[0] == redirection))
            counter++;
        temp = temp->next;
    }
    return (counter);
}

int here_doc_helper(t_here_doc_vars *vars, char *limiter, char **env)
{
    while (vars->entered_data)
    {
        if (!ft_strcmp(vars->entered_data, limiter))
            break ;
        write(vars->p[STD_OUTPUT], vars->entered_data, ft_strlen(vars->entered_data));
        write(vars->p[STD_OUTPUT], "\n", 2);
        free (vars->entered_data);
        vars->s = readline("> ");
		if (vars->s)
    		vars->entered_data = expanding(vars->s, env);
		else
		{
			g_key.after_exit = 1;
			if (g_key.flag == 6)
                printf(">\n");
            free (limiter);
            free (vars->entered_data);
			close(vars->p[STD_OUTPUT]);
			return (vars->p[STD_INPUT]);
		}
	}
    close(vars->p[STD_OUTPUT]);
    free (vars->entered_data);
    free (limiter);
    return (vars->p[STD_INPUT]);
}

int here_doc(char *limiter, char **env)
{
    t_here_doc_vars vars;

	g_key.flag_for_here = 1;
	vars.s = readline("> ");
	if (vars.s)
    	vars.entered_data = expanding(vars.s, env);
	else
	{
		g_key.after_exit = 1;
		if (g_key.flag == 6)
			printf(">\n");
		return (-4);
	}
	pipe(vars.p);
    limiter = remove_quotes(limiter);
    return (here_doc_helper(&vars, limiter, env));
}


// int here_doc(char *limiter, char **env)
// {
//     int     p[2];
// 	char	*s;
//     char    *entered_data;

//     pipe(p);
//     limiter = remove_quotes(limiter);
//     while (TRUE)
//     {
// 		g_key.flag_for_here = 1;
//         s = readline("> ");
//         if (s)
//     		entered_data = expanding(s, env);
// 		else
// 		{
// 			g_key.after_exit = 1;
// 			if (g_key.flag == 6)
// 				printf(">\n");
// 			close(p[STD_OUTPUT]);
// 			return (p[STD_INPUT]);
// 		}
//         if (!ft_strcmp(entered_data, limiter))
//             break ;
//         write(p[STD_OUTPUT], entered_data, ft_strlen(entered_data));
//         write(p[STD_OUTPUT], "\n", 2);
//         free (entered_data);
//     }
//     close(p[STD_OUTPUT]);
//     return (p[STD_INPUT]);
// }

void	heredoc_searcher(char **splitted_data, t_returned_data *returned_data, char **env)
{
    int     i;
    int     input_fd;
    int         in_quote;

    i = 0;
    in_quote = 0;
    while (splitted_data[i])
    {
        if (!ft_strcmp(splitted_data[i], "|"))
            returned_data = returned_data->next;
        else if (!ft_strcmp(splitted_data[i], "\""))
            in_a_quote(&in_quote, DOUBLE_QUOTE);
        else if (!ft_strcmp(splitted_data[i], "'"))
            in_a_quote(&in_quote, SINGLE_QUOTE);
        else if (!ft_strcmp(splitted_data[i], "<") && !ft_strcmp(splitted_data[i + 1], "<") && in_quote == 0)
        {
            i += 2;
            returned_data->input_fd =  here_doc(splitted_data[i], env);
			if (returned_data->input_fd == -4)
				g_key.flag = 6;
			g_key.flag_for_here = 0;
        }
        i++;
    }
}


void    add_to_list(t_list  **head, char *string)
{
    t_list *new;
    
    new = ft_lstnew(string);
    ft_lstadd_back(head, new);
}

t_list  *making_a_list(char **s)
{
    t_list *ctx;
    int     s_length;
    int i;

    s_length = get_length(s);
    ctx = malloc(sizeof(t_list) * (s_length));
    i = 0;
    ctx = NULL;
    while (s[i])
    {
        add_to_list(&ctx, s[i]);
        i++;
    }
    return (ctx);
}

void    add_space_helper(char *context, t_add_space_vars *vars)
{
        if ((context[vars->i] == RED_INPUT || context[vars->i] == RED_OUTPUT || context[vars->i] == PIPE))
        {
            vars->new_string[vars->j++] = context[vars->i];
            if (vars->in_quote == 0)
                vars->new_string[vars->j++] = SPACE;
        }
        else if ((context[vars->i + 1] == RED_INPUT || context[vars->i + 1] == RED_OUTPUT || context[vars->i + 1] == PIPE))
        {
            vars->new_string[vars->j++] = context[vars->i];
            if (vars->in_quote == 0)
                vars->new_string[vars->j++] = SPACE;
        }
        else
            vars->new_string[vars->j++] = context[vars->i];
}

char    *add_space(char *context, int redirections_counter)
{
    t_add_space_vars vars;

    vars.new_string_length = ft_strlen(context) + redirections_counter + 1;
    vars.new_string = malloc(sizeof(char) * (vars.new_string_length));
    vars.i = -1;
    vars.j = 0;
    vars.in_quote = 0;
    while (context[++(vars.i)])
    {
        if (context[vars.i] == DOUBLE_QUOTE)
            in_a_quote(&vars.in_quote, DOUBLE_QUOTE);
        else if (context[vars.i] == SINGLE_QUOTE)
            in_a_quote(&vars.in_quote, SINGLE_QUOTE);
        add_space_helper(context, &vars);
    }
    vars.new_string[vars.j] = '\0';
    return (vars.new_string);
}

char    *get_new_context(t_data *entered_data)
{
    int counter;
    int in_quote;

    entered_data->index = 0;
    counter = 0;
    in_quote = 0;
    while (entered_data->context[entered_data->index])
    {
        if (entered_data->context[entered_data->index] == SINGLE_QUOTE)
            replacing_space(entered_data, SINGLE_QUOTE);
        else if (entered_data->context[entered_data->index] == DOUBLE_QUOTE)
            replacing_space(entered_data, DOUBLE_QUOTE);
        else if ((entered_data->context[entered_data->index] == RED_INPUT || entered_data->context[entered_data->index] == RED_OUTPUT || entered_data->context[entered_data->index] == PIPE))
            counter+=2;
        entered_data->index++;
    }
    return (add_space(entered_data->context, counter));
}


void	returned_data_addback(t_returned_data **returned_data, t_returned_data *new)
{
	t_returned_data	*temp;

	temp = (*returned_data);
	if (*returned_data)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*returned_data = new;
}

void    create_returned_nodes(t_returned_data **returned_data, int commands_number)
{
    t_returned_data *new;
    while(commands_number > 0)
    {
        new = malloc(sizeof(t_returned_data));
        new->next = NULL;
        new->args = NULL;
        new->str_idx = 0;
        new->is_executable = TRUE;
        new->input_fd = STD_INPUT;
        new->output_fd = STD_OUTPUT;
        returned_data_addback(returned_data, new);
        commands_number--;
    }
}

int     find_heredoc_position(char **s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!ft_strcmp(s[i], "<"))
        {
            i++;
            if (!ft_strcmp(s[i], "<"))
            {
                if (!s[i + 2])
                    return (TRUE);
            }
        }
        i++;
    }
    return (FALSE);
}

int getting_input_fd(char *str, t_returned_data *returned_data, char **s)
{
    int     temp_input;
    int     i;

    i = -1;
    temp_input = returned_data->input_fd;
    while (s[++i])
    {
        if (!ft_strcmp(s[i], "<") && !ft_strcmp(s[i + 1], "<"))
            i+=2;
        else if (!ft_strcmp(s[i], "<"))
        {
            i++;
            returned_data->input_fd = open(s[i], O_RDONLY);
            if (returned_data->input_fd == -1)
            {
                printf("%s:%s\n", s[i], strerror(errno));
                returned_data->is_executable = FALSE;
                return (i);
            }
        }
    }
    if (find_heredoc_position(s))
        returned_data->input_fd = temp_input;
    return (i);
}

void    getting_output_fd(char *str, t_returned_data *returned_data, int unexisting_file_idx)
{
    char **s;
    int     i;
    char    *temp;

    s = ft_split(str, SPACE);
    i = 0;
    while (s[i] && i < unexisting_file_idx)
    {
        if (!ft_strcmp(s[i], ">"))
        {
            i++;
            if (returned_data->output_fd != 1)
                close (returned_data->output_fd);
            if (!ft_strcmp(s[i], ">"))
            {
                temp = remove_quotes(s[i + 1]);
                returned_data->output_fd = open(temp, O_WRONLY | O_CREAT | O_APPEND, 00400 | 00200);
                free (temp);
            }
            else
            {
                temp = remove_quotes(s[i]);
                returned_data->output_fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200);
                free (temp);
            }
            if (returned_data->output_fd == -1)
            {
                returned_data->is_executable = FALSE;
                printf("%s\n", strerror(errno));
                break ;
            }
        }
        i++;
    }
    ft_free(s);
}

void    get_cmd_args_helper(char **data, t_returned_data *returned_data, char **env)
{
    int i;
    int j;    

    i = 0;
    j = 0;
    while (data[i])
    {
        if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], ">"))
        {
            i++;
            if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], ">"))
                i++;
        }
        else
            returned_data->args[j++] = data[i];
        i++;
    }
    returned_data->cmd_dup = returned_data->args[0];
    returned_data->cmd_path = get_command_path(env, returned_data->args[0]);
    returned_data->args[j] = NULL;
}

int get_cmd_args(char **data, t_returned_data *returned_data, char **env)
{
    char **s;
    int k;
    int whole_length;

    whole_length = 0;
    k = 0;
    while (returned_data)
    {
        s = ft_split(data[k++], SPACE);
        whole_length = get_length(s) - get_args_length(s);
        if (whole_length == 0)
            return (FALSE);
        returned_data->args = malloc(sizeof(char *) * (whole_length + 1));
        get_cmd_args_helper(s, returned_data, env);
        returned_data = returned_data->next;
    }
    return (TRUE);
}


void    args_final_touch(t_returned_data *returned_data, char **env)
{
    char *temp;
    int i;
    
    while (returned_data)
    {
        i = 0;
        i = 0;
        while (returned_data->args[i])
        {
            back_space(returned_data->args[i]);
            temp = remove_quotes(returned_data->args[i]);
            returned_data->args[i] = temp;
            // free (temp);
            i++;
        }
        returned_data = returned_data->next;
    }
}

char    *expanding_join(char *s1, char *s2)
{
	size_t	total_len;
	size_t	i;
	size_t	j;
	char	*str;
		
	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
    free (s1);
	return (str);
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
    return (ft_strdup(""));
}

char *dollar_sign_found(t_data *data, char **env, char *saver, int *i)
{
    // int vars.index_saver;
    // char *vars.env_value;
    // char *vars.s1;
    // char *vars.s2;
    // char *vars.temp;
    // char *vars.temp1;
    t_dollar_sign_vars vars;

    data->index++;
    vars.env_value = NULL;
    vars.index_saver = data->index;
    if (!ft_isalnum(data->context[data->index]) && data->context[data->index] != UNDER_SCORE)
        return (ft_substr(data->context, 0, data->index + 1));
    while ((data->context[data->index]) && ((ft_isalnum(data->context[data->index])) || (data->context[data->index] == UNDER_SCORE)))
        data->index++;
    vars.s1 = ft_substr(data->context, *i, vars.index_saver - *i - 1);
    *i = data->index;
    vars.s2 = ft_substr(data->context, vars.index_saver, data->index - vars.index_saver);
    vars.temp = ft_substr(data->context, vars.index_saver + 1, data->index - vars.index_saver);
    vars.temp1 = ft_strdup("minishell");
    if (vars.s2[0] == ZERO)
        vars.env_value = ft_strjoin(vars.temp1, vars.temp);
    else
        vars.env_value = search_in_env(vars.s2, env);
    free(vars.temp);
    free(vars.temp1);
    free (vars.s2);
    saver = expanding_join(saver, expanding_join(vars.s1, vars.env_value));
    data->index--;
    return (saver);
}
void    expanding_helper(t_expanding *vars)
{
    if ((vars->data.context[vars->data.index] == RED_INPUT) && (vars->data.context[vars->data.index + 1] == RED_INPUT))
        vars->is_limiter = TRUE;
    else if (vars->data.context[vars->data.index] == SPACE)
        vars->is_limiter = FALSE;
    else if (vars->data.context[vars->data.index] == DOUBLE_QUOTE)
        in_a_quote(&vars->in_quote, DOUBLE_QUOTE);
    else if (vars->data.context[vars->data.index] == SINGLE_QUOTE)
        in_a_quote(&vars->in_quote, SINGLE_QUOTE);
}

char    *expanding(char *str, char **env)
{
   t_expanding vars;

    vars.in_quote = 0;
    vars.is_limiter = FALSE;
    vars.saver = NULL;
    vars.data.context = str;
    vars.data.index = 0;
    vars.j = 0;
    vars.x = 0;
    while (vars.data.context[vars.data.index])
    {
        expanding_helper(&vars);
        if ((vars.data.context[vars.data.index] == DOLLAR_SIGN) && (vars.in_quote != SINGLE_QUOTE) && (vars.is_limiter == FALSE))
        {
            vars.saver = dollar_sign_found(&vars.data, env, vars.saver, &vars.j);
            vars.x = vars.data.index + 1;
        }
        if (!vars.data.context[vars.data.index])
            break ;
        vars.data.index++;
    }
    vars.temp = ft_substr(vars.data.context, vars.x, ft_strlen(vars.data.context) - vars.x);
    if (vars.x < vars.data.index)
        vars.saver = expanding_join(vars.saver, vars.temp);
    free (vars.temp);
    free (str);
    return (vars.saver);
}

char    **get_new_env(t_list *env)
{
    int length;
    int i;
    char    **new_env;


    length = ft_lstsize(env);
    new_env = malloc(sizeof(char *) * (length + 1));
    i = 0;
    while(env)
    {
        new_env[i] = env->content;
        env = env->next;
		i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

void    getting_input_output_fd(char *str, t_returned_data *temp)
{
    int unexisting_file_idx;
    char **s;

    s = ft_split(str, SPACE);
    unexisting_file_idx = getting_input_fd(str, temp, s);
    ft_free (s);
    getting_output_fd(str, temp, unexisting_file_idx);
}

void    pipe_handling(int commands_number, char **splitted_by_pipe, t_returned_data *temp)
{
    int (*pipes_array)[2];
    int i;

    i = -1;
    pipes_array = malloc(sizeof(int *) * (commands_number - 1));
    while (splitted_by_pipe[++i])
    {
		if (commands_number > 1)
		{
			if (i < commands_number - 1)
				pipe(pipes_array[i]);
			if (i == 0)
				temp->output_fd = pipes_array[i][STD_OUTPUT];
			else if (i == commands_number - 1)
                temp->input_fd = pipes_array[i - 1][STD_INPUT];
			else
			{
                temp->input_fd = pipes_array[i - 1][STD_INPUT];
				temp->output_fd = pipes_array[i][STD_OUTPUT];
			} 
		}
        getting_input_output_fd(splitted_by_pipe[i], temp);
        temp = temp->next;
    }
    free (pipes_array);
}

int	preparing(t_data *entered_data, t_list *env, t_returned_data **returned_data)
{
    char            **splitted_by_space;
    char            **splitted_by_pipe;
    char            **new_env;
    int             commands_number;


    new_env = get_new_env(env);
    entered_data->context = expanding(entered_data->context, new_env);
    entered_data->context = get_new_context(entered_data);
    splitted_by_pipe = ft_split(entered_data->context, PIPE);
    commands_number = get_length(splitted_by_pipe);
    splitted_by_space = ft_split(entered_data->context, SPACE);
    create_returned_nodes(returned_data, commands_number);
    heredoc_searcher(splitted_by_space, *returned_data, new_env);
    pipe_handling(commands_number, splitted_by_pipe, *returned_data);
    if (get_cmd_args(splitted_by_pipe, *returned_data, new_env))
        args_final_touch(*returned_data, new_env);
	else
    {
        ft_free(splitted_by_pipe);
        ft_free(splitted_by_space);
		return (-1);
    }
    ft_free(splitted_by_pipe);
    ft_free(splitted_by_space);
	return (1);
}
void    prompt(char **env, t_list *new_env)
{
    t_data entered_data;
    t_returned_data *returned_data;
    
    returned_data = NULL;
    entered_data.context = readline("minishell : ");
    if (entered_data.context == NULL)
	{
		printf("exit\n");
    	ft_exit(g_key.exit_stat, NULL);
	}
	if (ft_strlen(entered_data.context) == 0)
        return ;
    if (g_key.after_exit == 1 && entered_data.context)
    	g_key.after_exit = 0;
    add_history(entered_data.context);
    if (error_handling(entered_data.context))
    {
        printf("error occured\n");
        return  ;
    }
    if (preparing(&entered_data, new_env, &returned_data) == -1 || g_key.flag == 6)
    	return ;
    fill_list(returned_data, env, &new_env);
    ft_free(returned_data->args);
    free(returned_data->cmd_path);
    free (entered_data.context);
}
int main(int ac, char **av,  char **env)
{
	t_list	*new_env;
	struct termios termios_save;
	struct termios termios_new;

	if (ac != 1)
	{
		printf("Too many arguments\n");
        exit (1);
	}
	create_list(env, &new_env);
	g_key.flag_for_here = 0;
	g_key.after_exit = 0;
    while (TRUE)
    {
		g_key.flag = 0;
		dup2(g_key.saver, 0);
		tcgetattr(0, &termios_save);
		termios_new = termios_save;
		termios_new.c_lflag &= ~(ECHOCTL);
		tcsetattr(0, 0, &termios_new);
		// signal (SIGINT, &sig_handler);
		// signal(SIGQUIT, SIG_IGN);`
        prompt(env, new_env);
        // system("leaks minishell");
        // break;
    }
}