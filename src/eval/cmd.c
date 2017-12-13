/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:14:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static inline void	eval_bi_cmd(t_sh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	if (av)
	{
		ft_vstr_ctor(av);
		ft_vstr_pushc(av, exe);
	}
	while ((end = sh_peek(self)) && end->id)
	{
		if (end->id == SH_TOK_WORD && av)
			ft_vstr_pushc(av, ft_tok_ident(end)->buf);
		else if (end->id != SH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		sh_next(self, NULL);
	}
	if (av)
	{
		ft_vstr_grow(av, 1);
		FT_INIT(ft_vstr_end(av), char *);
	}
}

inline int			sh_eval_cmd(t_sh *self, t_job **pjob, t_tok *tok)
{
	t_vstr	av;
	int		st;
	t_job	job;
	t_job	hdoc;

	if (tok->id != SH_TOK_WORD)
		return (SH_NEXT);
	eval_bi_cmd(self, &av, ft_tok_ident(tok)->buf);
	if ((st = ft_job_cmd(&job, "PATH", av.buf, self->env.buf)) < 0)
		return (WUT);
	else if (st)
		return (ft_retf(SH_NOK, N_SH"%s: Command not found\n", av.buf[0]));
	if ((tok = sh_skip(self, "\t ")) && tok->id == SH_TOK_HEREDOC)
	{
		sh_next(self, NULL);
		ft_job_output(&hdoc, ft_tok_ident(tok)->buf);
		*pjob = ft_worker_push(&self->worker, &hdoc);
		ft_job_pipe(*pjob);
	}
	ft_job_data(&job, self);
	*pjob = ft_worker_push(&self->worker, &job);
	return (SH_NOK);
}