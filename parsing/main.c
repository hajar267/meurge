/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:22:19 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/07 12:56:34 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void f()
{
	system("leaks minishell");
}

int	convert_it(char *line, t_token **head_ref, t_link *envp)
{
    t_token	*token;
    t_token	*current;
    t_token	*last;
	t_token	*tmp;

	token = ft_tokenizer(line, envp);
	current = NULL;
	if (token == NULL)
		return (-1);
    while (token)
    {
        current = ft_malloc_gab(sizeof(t_token), 0);
        current->content = ft_strdup(token->content);
        current->next = NULL;
		current->prev = NULL;
        if (*head_ref == NULL)
            *head_ref = current;
        else
        {
			last = *head_ref;
            while (last->next!= NULL)
                last = last->next;
            last->next = current;
			current->prev = last;
        }
		tmp = token->next;
		token = tmp;
    }
	return (1);
}

// int	check_for_empty(t_token	*tokens)
// {
// 	while (tokens)
// 	{
// 		if (tokens->content[0] == '\0')
// 			return (-1);
// 		tokens = tokens->next;
// 	}
// 	return (1);
// }

t_cmds	*read_line(t_link *envp)
{
	t_token	*tok;
	t_cmds	*commands;
	char	*line;
	t_token *tmp;

	line = ft_strdup_del(readline("my_bash-4.5$ "));
	if (!line)
	{
		write(1, "my_bash-4.5$ exit\n", 18);
		ft_malloc_gab(0, 1);
		exit(exit_status(0, 0));
	}
	if (line[0] == '\0')
		return (NULL);
	add_history(line);
	tok = NULL;
	commands = NULL;
	if (!line)
		return (NULL);
	if (convert_it(line, &tok, envp) == -1)
		return (NULL);
	if (enumeration(tok) == -1)
		return (NULL);
		// while(tok)
		// {
		// 	printf("tok : %s\n", tok->content);
		// 	tok=tok->next;
		// }
	if (check_for_pipe(tok) == -1)
		return (NULL);
	check_for_cmd_red_args(&tok);
	convert_to_new_list(tok, &commands);
	heredoc(commands, envp);
	if (ft_open_files(commands) == -1)
		return (NULL);
	while(tok)
	{
		tmp = tok->next;
		tok = tmp;
	}
	return (commands);
}

int    ft_numb_pipe(t_cmds    *cmds)
{
    int i = 0;
    while (cmds)
    {
        if (ft_strcmp(cmds->data[0], "|") == 0)
            i++;
        cmds = cmds->next;
    }
    return (i);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	atexit(f);
	t_link	*envp;
	int flag;
	flag = 0;
	if (!isatty(ttyslot()))
		return (printf("tty required\n"), 0);
	if (*env == NULL)
	{
		envp = make_my_own_env();
		flag = 1;
	}
	else
		envp = env_linkedlist(env);
	
	// t_node *tmp1 = envp->head;
	// while (tmp1)
	// {
	// 	t_env *env = tmp1->data;
	// 	printf("%s : %s\n", env->key, env->val);
	// 	tmp1 = tmp1->next;
	// }
	// rl_catch_signals = 0;
	// signal(SIGINT, handle_siginit);
	// signal(SIGQUIT, SIG_IGN);
	while(true)
	{
		t_cmds *commands = read_line(envp);
		if (!commands)
			continue;
		cho(commands, envp, flag);
		// while(commands)
		// {
		// 	int i = 0;
		// 	while(commands->data[i])
		// 	{
		// 		printf("data : %s\n", commands->data[i]);
		// 		i++;
		// 	}
		// 	printf("---------------------\n");
		// 	printf("fd_redir: %d\nfd_heredoc: %d\n", commands->fd, commands->fd_h);
		// 	printf("---------------------");
		// 	printf("----\n");
			// commands = commands ->next;
		// }
	}
	return 0;
}
