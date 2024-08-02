/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:22:19 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/02 21:27:46 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int convert_it(char *line, t_token **head_ref)
{
    t_token *token = ft_tokenizer(line);
	if (token == NULL)
		return (-1);
    t_token *current = NULL;

    while (token)
    {
        current = malloc(sizeof(t_token));
		if (!current)
			return (-1);
        current->content = ft_strdup(token->content);
        current->next = NULL;
		current->prev = NULL;

        if (*head_ref == NULL)
            *head_ref = current;
        else
        {
            t_token *last = *head_ref;
            while (last->next!= NULL)
                last = last->next;
            last->next = current;
			current->prev = last;
        }
		t_token	*tmp = token->next;
        free(token->content);
        free(token);
		token = tmp;
    }
	return (1);
}

int	check_for_empty(t_token	*tokens)
{
	while (tokens)
	{
		if (tokens->content[0] == '\0')
			return (-1);
		tokens = tokens->next;
	}
	return (1);
}

t_cmds	*read_line(void)
{
	char* line = readline("my_bash-4.5$ ");
	if (!line)
		return (NULL) ;
	t_token *tok = NULL;
	t_cmds	*commands =NULL;
	if (convert_it(line, &tok) == -1)
		return (NULL) ;
	// we enum just into " " for $
	free(line);
	if (check_for_empty(tok) == -1)
		return (NULL);
	check_for_pipe(tok);
	enumeration(tok);
	check_for_cmd_red_args(&tok);
	convert_to_new_list(tok, &commands);
	heredoc(commands);
	ft_open_files(commands);
	while(tok)
	{
		t_token *tmp = tok->next;
		free(tok->content);
		free(tok);
		tok = tmp;
	}
	return (commands);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_link	*envp;
	int flag;
	flag = 0;
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
	while(true)
	{
		t_cmds *commands = read_line();
		if (!commands)
		{
			write(1, "my_bash-4.5$ exit\n", 18);
			ft_malloc_gab(0, 1);
			exit(exit_status(0, 0));
		}
		rl_catch_signals = 0;
		if (isatty(STDIN_FILENO))
		{
			signal(SIGINT, handle_siginit);
			signal(SIGQUIT, SIG_IGN);
		}
		cho(commands, envp, flag);
		// while(commands)
		// {
		// 	int i = 0;
		// 	while(commands->data[i])
		// 	{
		// 		printf("data : %s\n", commands->data[i]);
		// 		i++;
		// 	}
		// 	printf("----\n");
		// 	commands = commands ->next;
		// }
	}
}

/*
	ther is a method to implimentate the << the we can call the readline another time 
	in infinite loop and take her > to print it and then we save each line in a char ** or in a file 
	and then we applicate the command before << to the file
*/