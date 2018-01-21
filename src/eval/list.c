/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	onsemicolon(t_job *job, int fd, t_deq *toks, char **ln)
{
	int st;

	sh_toknext(toks);
	if (job->processes.len)
	{
		g_shstatus = job->processes.len ? sh_joblaunch(job, 1) : job->status;
		ft_vecclr((t_vec *)&job->processes, (t_dtor)sh_procdtor);
	}
	if ((st = sh_evalandor(job, fd, toks, ln)))
	{
		sh_jobdtor(job);
		return (st);
	}
	return (YEP);
}

static inline int	onamp(t_job *job, int fd, t_deq *toks, char **ln)
{
	int st;

	if (!g_shinteract)
		return (onsemicolon(job, fd, toks, ln));
	sh_toknext(toks);
	sh_poolpush(job);
	sh_jobctor(job);
	if ((st = sh_evalandor(job, fd, toks, ln)))
	{
		sh_jobdtor(job);
		return (st);
	}
	return (YEP);
}

static inline int	oneof(t_job *job)
{
	g_shstatus = job->processes.len ? sh_joblaunch(job, 1) : job->status;
	sh_jobdtor(job);
	return (YEP);
}

inline int			sh_evallist(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	job;
	int		st;

	sh_jobctor(&job);
	if (sh_evalandor(&job, fd, toks, ln) == ERR)
		return (ERR);
	while (1)
		if (!(tok = sh_tokpeek(toks)))
		{
			sh_jobdtor(&job);
			return (YEP);
		}
		else if (tok->id == TOK_AMP)
		{
			if ((st = onamp(&job, fd, toks, ln)))
				return (st == NOP ? YEP : st);
		}
		else if (tok->id == TOK_SEMICOLON)
		{
			if ((st = onsemicolon(&job, fd, toks, ln)))
				return (st == NOP ? YEP : st);
		}
		else if (tok->id == TOK_END || tok->id == TOK_EOL)
			return (oneof(&job));
		else
		{
			sh_jobdtor(&job);
			return (YEP);
		}
}