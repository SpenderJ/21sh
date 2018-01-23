/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	ouput(int ac, char **av, char **envv)
{
	(void)ac;
	(void)envv;
	ft_putf(STDOUT_FILENO, av[0]);
	return (EXIT_SUCCESS);
}

inline int			sh_evalheredoc(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	size_t	i;
	t_tok	*op;
	t_proc	out;
	t_proc	*proc;

	(void)ln;
	op = sh_tokpeek(toks);
	tok = sh_toknext(toks);
	i = job->procs.len - 1;
	proc = ft_vecat((t_vec *)&job->procs, i);
	if (ft_isdigit(*op->val))
		proc->src[STDIN_FILENO] = *op->val - '0';
	if (i > 0 && job->procs.buf[i - 1].u.fn == ouput)
	{
		free(job->procs.buf[i - 1].argv[0]);
		job->procs.buf[i - 1].argv[0] = ft_strdup(tok->val);
	}
	else
	{
		sh_procfn(&out, ouput, NULL);
		out.argv = ft_malloc(2 * sizeof(char **));
		out.argv[0] = ft_strdup(tok->val);
		out.argv[1] = NULL;
		ft_veccput((t_vec *)&job->procs, i, &out);
	}
	sh_toknext(toks);
	return (YEP);
}
