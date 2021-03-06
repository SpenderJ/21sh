/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define ISCMDM(T) ((T)->id==TOK_WORD||TOK_ISBOOL((T)->id)||TOK_ISREDIR((T)->id))

static int		evalexport(t_map *vars)
{
	uint32_t it;

	if (!vars->len)
		return (NOP);
	it = 0;
	while (it < vars->cap)
	{
		if (BUCKET_ISPOPULATED(vars->bucks, it))
			sh_varset(((char **)vars->keys)[it], ((char **)vars->vals)[it]);
		++it;
	}
	ft_mapdtor(vars, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
	return (YEP);
}

static int		argverror(t_job *job)
{
	t_proc *proc;
	t_proc *prev;

	proc = ft_vecback((t_vec *)&job->procs);
	ft_vecpop((t_vec *)&job->procs, NULL);
	if (proc->piped)
	{
		prev = ft_vecback((t_vec *)&job->procs);
		ft_vecpop((t_vec *)&job->procs, NULL);
		sh_procdtor(prev);
	}
	sh_procdtor(proc);
	if (job->procs.len == 0)
	{
		ft_vecdtor((t_vec *)&job->procs, NULL);
		job->procs.isz = sizeof(t_proc);
	}
	return (OUF);
}

inline int		sh_evalsimple(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_map	vars;

	(void)fd;
	ft_mapctor(&vars, g_strhash, sizeof(char *), sizeof(char *));
	if ((tok = sh_tokpeek(toks))->id == TOK_WORD)
		if (ft_strchr(tok->val, '='))
			sh_evalassign(toks, &vars);
	tok = sh_tokpeek(toks);
	sh_procnone(ft_vecpush((t_vec *)&job->procs));
	while (tok && TOK_ISREDIR(tok->id))
		if (sh_evalredir(job, toks, ln) == OUF)
			return (OUF);
		else
			tok = sh_tokpeek(toks);
	if (((t_proc *)ft_vecback((t_vec *)&job->procs))->kind == PROC_ERR)
		while (tok && ISCMDM(tok))
			tok = sh_toknext(toks);
	else if (ISCMDM(tok))
		return (sh_evalargv(job, &vars, toks, ln) ? argverror(job) : YEP);
	return (evalexport(&vars));
}
