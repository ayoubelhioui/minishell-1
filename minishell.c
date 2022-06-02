
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

void    replacing_space(t_data *entered_data, char quote)
{
    entered_data->index++;
    while (entered_data->context[entered_data->index] && entered_data->context[entered_data->index] != quote)
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

char    *remove_quotes(char *context)
{
    char    *new_string;
    int      i;
    int      j;

    int length = allocation_length(context);
    new_string = malloc(sizeof(char) * (length + 1));
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

int here_doc(char *limiter)
{
    int p[2];
    t_returned_data *returned_data;
    
    returned_data->heredoc_data = readline("> ");
    pipe(p);
    limiter = remove_quotes(limiter);
    while (returned_data->heredoc_data)
    {
        if (!ft_strcmp(returned_data->heredoc_data, limiter))
            break ;
        write(p[STD_OUTPUT], returned_data->heredoc_data, ft_strlen(returned_data->heredoc_data));
        write(p[STD_OUTPUT], "\n", 2);
        free (returned_data->heredoc_data);
        returned_data->heredoc_data = readline("> ");
    }
    close(p[STD_OUTPUT]);
    return (p[STD_INPUT]);
}


void    in_a_quote(int *in_quote, int SINGLE_OR_DOUBLE)
{
    if (*in_quote == SINGLE_OR_DOUBLE)
        *in_quote = 0;
    else if (*in_quote == 0)
        *in_quote = SINGLE_OR_DOUBLE;
}

void    heredoc_searcher(char **splitted_data, t_returned_data *returned_data)
{
    int     i;
    int     input_fd;
    t_returned_data *temp;
    int         in_quote;

    i = 0;
    temp = returned_data;
    in_quote = 0;
    while (splitted_data[i])
    {
        if (!ft_strcmp(splitted_data[i], "|"))
            temp = temp->next;
        else if (!ft_strcmp(splitted_data[i], "\""))
            in_a_quote(&in_quote, DOUBLE_QUOTE);
        else if (!ft_strcmp(splitted_data[i], "'"))
            in_a_quote(&in_quote, SINGLE_QUOTE);
        else if (!ft_strcmp(splitted_data[i], "<") && !ft_strcmp(splitted_data[i + 1], "<") && in_quote == 0)
        {
            i += 2;
            temp->input_fd = here_doc(splitted_data[i]);
        }
        i++;
    }
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
    // search_for_token(&ctx);  
}

char    *add_space(char *context, int redirections_counter)
{
    int i;
    int j;
    int new_string_length;
    char *new_string;
    int  in_quote;

    new_string_length = ft_strlen(context) + redirections_counter + 1;
    new_string = malloc(sizeof(char) * (new_string_length));
    i = 0;
    j = 0;
    in_quote = 0;
    while (i < new_string_length)
    {
        if (context[i] == DOUBLE_QUOTE)
            in_a_quote(&in_quote, DOUBLE_QUOTE);
        else if (context[i] == SINGLE_QUOTE)
            in_a_quote(&in_quote, SINGLE_QUOTE);
        if ((context[i] == RED_INPUT || context[i] == RED_OUTPUT || context[i] == PIPE))
        {
            new_string[j++] = context[i];
            if (in_quote == 0)
                new_string[j++] = SPACE;
        }
        else if ((context[i + 1] == RED_INPUT || context[i + 1] == RED_OUTPUT || context[i + 1] == PIPE))
        {
            new_string[j++] = context[i];
            if (in_quote == 0)
                new_string[j++] = SPACE;
        }
        else
            new_string[j++] = context[i];
        i++;
    }
    new_string[j] = '\0';
    return (new_string);
}

char    *get_new_context(t_data *entered_data)
{
    int counter;
    int in_quote;

    entered_data->index = 0;
    counter = 0;
    in_quote = 0;
    // expanding();
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

void    getting_input_fd(char *str, t_returned_data *returned_data)
{
    char **s;
    t_returned_data *temp;
    int temp_input;
    int     i;
    temp = returned_data;
    s = ft_split(str, SPACE);
    i = 0;
    temp_input = temp->input_fd;
    while (s[i])
    {
        if (!ft_strcmp(s[i], "<") && !ft_strcmp(s[i + 1], "<"))
            i+=2;
        if (!ft_strcmp(s[i], "<"))
        {
            i++;
            temp->input_fd = open(s[i], O_RDONLY);
            if (temp->input_fd == -1)
            {
                printf("%s:%s\n", s[i], strerror(errno));
                temp->is_executable = FALSE;
                break ;
            }
        }
        i++;
    }
    if (find_heredoc_position(s))
        temp->input_fd = temp_input;
}

void    getting_output_fd(char *str, t_returned_data *returned_data)
{
    char **s;
    int     i;
    t_returned_data *temp;

    s = ft_split(str, SPACE);
    temp = returned_data;
    i = 0;
    while (s[i])
    {
        if (!ft_strcmp(s[i], ">"))
        {
            i++;
            if (temp->output_fd != 1)
                close (temp->output_fd);
            if (!ft_strcmp(s[i], ">"))
                temp->output_fd = open(remove_quotes(s[i + 1]), O_WRONLY | O_CREAT | O_APPEND, 00400 | 00200);
            else
                temp->output_fd = open(remove_quotes(s[i]), O_WRONLY | O_CREAT, 00400| 00200);
            if (temp->output_fd == -1)
            {
                printf("%s\n", strerror(errno));
                break ;
            }
        }
        i++;
    }
}


void     get_cmd_args(char **data, t_returned_data *returned_data, char **env)
{
    char **s;
    int length;
    int i;
    int j;
    int k;
    t_returned_data *temp;
    temp = returned_data;
    k = 0;
    while (temp && data[k])
    {
        s = ft_split(data[k], SPACE);
        length = get_args_length(s);
        temp->args = malloc(sizeof(char *) * (get_length(s) - length));
        j = 0;
        i = 1;
        temp->cmd_path = get_command_path(env, s[0]);
        while (s[i])
        {
            if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
            {
                i++;
                if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">"))
                    i++;
            }            
            else
                temp->args[j++] = s[i];
            i++;
        }
        temp->args[j] = NULL;
        temp = temp->next;
        k++;
    }
}


void    args_final_touch(t_returned_data *returned_data, char **env)
{
    t_returned_data *temp;
    int i;
    
    temp = returned_data;
    while (temp)
    {
        i = 0;
        printf("-------------\n");
        i = 0;
        while (temp->args[i])
        {
            back_space(temp->args[i]);
            temp->args[i] = remove_quotes(temp->args[i]);
            i++;
        }
        i = 0;
        printf("The cmd Is : %s\n", temp->cmd_path);
        while (temp->args[i])
            printf("After : %s\n", temp->args[i++]);
        temp = temp->next;
    }
}
void    expanding_join(char *s1, char *s2)
{
	size_t	total_len;
	size_t	i;
	size_t	j;
	char	*str;

	if (!s2)
		return (NULL);
		
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
	return (str);
}
void    dollar_sign_found(t_data *entered_data, char **env)
{

}

void    expanding(t_data *entered_data, char **env)
{
    int in_a_quote;
    int is_limiter;
    int saver;

    in_a_quote = 0;
    is_limiter = 0;
    saver = NULL;
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
            dollar_sign_found(entered_data, env);
        entered_data->index++;
    }
}

void    preparing(t_data *entered_data, char **env, t_returned_data **returned_data)
{
    t_list          *data_list;
    char            **splitted_by_space;
    char            **splitted_by_pipe;
    int             commands_number;
    int             i;
    int             (*pipes_array)[2];


    entered_data->context = get_new_context(entered_data);
    expanding(entered_data, env);
    splitted_by_pipe = ft_split(entered_data->context, PIPE);
    commands_number = get_length(splitted_by_pipe);
    pipes_array = malloc(sizeof(int *) * (commands_number - 1));
    splitted_by_space = ft_split(entered_data->context, SPACE);
    create_returned_nodes(returned_data, commands_number);
    heredoc_searcher(splitted_by_space, *returned_data);
    t_returned_data *temp = *returned_data;
    t_returned_data *temp1 = *returned_data;
    char s;
    while (temp1)
    {
        while (read(temp1->input_fd, &s, 1))
            write(1, &s, 1);
        temp1 = temp1->next;
    }
    while (splitted_by_pipe[i])
    {
        if (i < commands_number - 1)
            pipe(pipes_array[i]);
        if (i == 0)
            temp->output_fd = pipes_array[i][STD_OUTPUT];
        else if (i == commands_number - 1)
        {
            if (temp->input_fd == 0)
                temp->input_fd = pipes_array[i - 1][STD_INPUT];
        }
        else
        {
            if (temp->input_fd == 0)
                temp->input_fd = pipes_array[i - 1][STD_INPUT];
            temp->output_fd = pipes_array[i][STD_OUTPUT];
        } 
        getting_input_fd(splitted_by_pipe[i], temp);
        getting_output_fd(splitted_by_pipe[i], temp);
        temp = temp->next;
        i++;
    }
    get_cmd_args(splitted_by_pipe, *returned_data, env);
    args_final_touch(*returned_data, env);
}


int main(int ac, char **av, char **env)
{
	struct sigaction sa;
    t_data entered_data;
    t_returned_data *returned_data;
	t_list	*env_l;
	t_returned_data	*en_t;
    
	if (ac != 1)
        exit (1);
	// sa.sa_handler = &sig_handler;
	// sa.sa_flags =  SA_RESTART;
	// sigaction (SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);
    returned_data = NULL;
	create_list(env, &env_l);
	fill_list(&en_t);
    while (TRUE)
    {
        entered_data.context = readline("minishell : ");
		if (entered_data.context == NULL)
			break ;
        if (ft_strlen(entered_data.context) == 0)
            continue;
		// built_check(entered_data.context, &env_l);
        add_history(entered_data.context);
        if (check_unclosed_quotes(entered_data.context))
        {
            printf("Missing Quote!\n");
            continue ;
        }
        preparing(&entered_data, env, &returned_data);
        free (entered_data.context);
        // quotes_handling(&entered_data, &returned_data, env);
    }
	// ft_free_list(&env_l);
}