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
        if (ft_strlen(temp->content) && temp->content[0] == redirection)
            counter++;
        temp = temp->next;
    }
    return (counter);
}

void    here_doc()
{
     char *s;
     
}

int getting_fd(t_list *splitted_data, char redirection)
{
    int counter;
    int fd;
    int i;

    counter = redirection_counter(splitted_data, redirection);
    i = 0;
    while (i < counter)
    {
        if ((ft_strlen(splitted_data->content) == 1) && (splitted_data->content[0] == redirection))
        {
            splitted_data = splitted_data->next;
            if ((ft_strlen(splitted_data->content) == 1) && (splitted_data->content[0] == redirection))
            {
                if (redirection == RED_INPUT)
                    here_doc();
                else
                    fd = open(splitted_data->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
                splitted_data = splitted_data->next;
            }
            else
                fd = open(splitted_data->content, O_WRONLY | O_CREAT, 0777);
            i++;
        }
        printf("Im Here : %s\n", splitted_data->content);
        splitted_data = splitted_data->next;
    }
    return (fd);
}

void    in_a_quote(int *in_quote, int quote)
{
    if (*in_quote == quote)
        *in_quote = 0;
    else if (*in_quote == 0)
        *in_quote = quote;
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

char    *add_space(char *context, int start_position, int redirections_counter)
{
    int i;
    int j;
    int new_string_length;
    char *new_string;

    new_string_length = ft_strlen(context) + redirections_counter + 1;
    new_string = malloc(sizeof(char) * (new_string_length));
    i = 0;
    j = 0;
    while (i < new_string_length)
    {
        if ((context[i] == RED_INPUT || context[i] == RED_OUTPUT) && i >= start_position)
        {
            new_string[j] = context[i];
            j++;
            new_string[j] = SPACE;
            j++;
        }
        else if ((context[i + 1] == RED_INPUT || context[i + 1] == RED_OUTPUT) && i >= start_position)
        {
            new_string[j] = context[i];
            j++;
            new_string[j] = SPACE;
            j++;
        }
        else
        {
            new_string[j] = context[i];
            j++;
        }
        i++;
    }
    printf("The New String Is : %s\n", new_string);
    return (new_string);
}



void    red_input(char *context)
{}

void    red_output(char **splitted_data)
{
    int i;

    i = 0;
    while (splitted_data[i])
    {

    }
}

char    *get_new_context(t_data *entered_data)
{
    int counter;
    int first_red_position;
    int in_quote;

    entered_data->index = 0;
    counter = 0;
    in_quote = 0;
    first_red_position = 0;
    while (entered_data->context[entered_data->index])
    {
        if (entered_data->context[entered_data->index] == SINGLE_QUOTE)
        {
            replacing_space(entered_data, SINGLE_QUOTE);
            in_a_quote(&in_quote, SINGLE_QUOTE);
        }
        else if (entered_data->context[entered_data->index] == DOUBLE_QUOTE)
        {
            replacing_space(entered_data, DOUBLE_QUOTE);
            in_a_quote(&in_quote, DOUBLE_QUOTE);
        }
        if ((entered_data->context[entered_data->index] == RED_INPUT || entered_data->context[entered_data->index] == RED_OUTPUT) && (in_quote == 0))
        {
            counter+=2;
            if (first_red_position == 0)
                first_red_position = entered_data->index;
        }
        entered_data->index++;
    }
    return (add_space(entered_data->context, first_red_position, counter));
}

void    preparing(t_data *entered_data, char **env)
{
    // t_returned_data *returned_data;
    // int             i;
    t_list *data_list;
    (void)env;
    char            **splitted_data;
    // int             array_length;
    entered_data->context = get_new_context(entered_data);
    splitted_data = ft_split(entered_data->context, ' ');
    data_list = making_a_list(splitted_data);
    t_list *d = data_list;
    while (d)
    {
        printf("Data Is : %s\n", d->content);
        d = d->next;
    }
    int input_fd = getting_fd(data_list, RED_OUTPUT);
    // printf("IT Is : %d\n", input_fd);    
    dprintf(input_fd, "Hey Dude");
    // determination(entered_data);
    // int i = 0;
    // while (splitted_data[i])
    //     printf("It Is : %s\n", splitted_data[i++]);
    // ft_free(splitted_data);
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
	struct sigaction sa;
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
        if (ft_strlen(entered_data.context) == 0)
            continue;
		built_check(entered_data.context, &env_l);
        add_history(entered_data.context);
        if (check_unclosed_quotes(entered_data.context))
        {
            printf("Missing Quote!\n");
            continue ;
        }
        preparing(&entered_data, env);
        free (entered_data.context);
        // quotes_handling(&entered_data, &returned_data, env);
    }
}