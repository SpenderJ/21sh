/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/rin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define EXPTD "Expected `<filename>' got `%s'"

inline int		sh_evalrin(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	redir;
	t_tok	*op;

	op = sh_tokpeek(toks);
	if ((tok = sh_toknext(toks))->id != TOK_WORD)
		return (sh_evalerr(*ln, tok, EXPTD, sh_tokstr(tok)));
	proc = job && job->procs.len ? ft_vecback((t_vec *)&job->procs) : NULL;
	if (tok->id == TOK_WORD)
	{
		if (ft_isdigit(*op->val))
			redir.from = *op->val - '0';
		else
			redir.from = STDIN_FILENO;
		if ((redir.to = open(tok->val, O_RDONLY, 0644)) < 0)
			return (sh_evalerr(*ln, tok, "%s: %e", tok->val, errno));
		if (proc)
			*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) = redir;
		else
			g_shstatus = 0;
		sh_toknext(toks);
	}
	return (YEP);
}
