int		i;
	char	**split_arg;

	i = 0;
	split_arg = NULL;
	g_key.exit_stat = 0;
	change_path_value(env);
	if (*args == NULL)
		sort_list(*env);
	while (args[i])
	{
		if (args[i][0] != '=')
			split_arg = split_with_equ(args[i]);
		if (!check_if_valid(args[i]) || args[i][0] == '=')
		{
			export_error(split_arg, args, &i);
			continue ;
		}
		else if (ft_isnode(env, args[i]))
			get_things_changed(args[i], env);
		else
			add_it_back(split_arg, args[i], env);
		ft_free(split_arg);
		i++;
	}
	g_key.cd_flag = 0;