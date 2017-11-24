/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_scan.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

static inline t_ret		lexer_scan_one(t_lexer *self, char peek, t_src *src)
{
	t_ret	r;
	t_tok	t;
	t_tokv	*val;
	t_lrule	*rule;

	FT_INIT(&t, t_tok);
	t.loc = src->cur;
	if (!ft_vec_grow(&self->vals, 1))
		return (RET_ERR);
	val = ft_vec_end(&self->vals);
	FT_INIT(val, t_tokv);
	t.val = val;
	rule = (t_lrule *)ft_vec_begin(&self->rules) - 1;
	while (++rule < (t_lrule *)ft_vec_end(&self->rules))
		if ((r = (*rule)(&t, peek, src)) == RET_ERR)
			return (RET_ERR);
		else if (r == RET_OK)
		{
			if ((t.loc.len = (uint16_t)(src->cur.cur - t.loc.cur)) && t.val)
				++self->vals.len;
			return (ft_deq_pushc(&self->toks, &t) ? RET_OK : RET_ERR);
		}
		else if ((r = ft_src_peek(src, &peek, 0)) != RET_OK)
			return (r);
	return (RET_NOK);
}

inline ssize_t			ft_lexer_scan(t_lexer *self, size_t n)
{
	size_t	c;
	t_src	*src;
	char	peek;
	t_ret	r;

	c = 0;
	while (c < n)
	{
		if (ft_deq_size(&self->srcs) == 0)
			break ;
		src = ft_deq_at(&self->srcs, 0);
		if ((r = ft_src_peek(src, &peek, 0)) == RET_ERR)
			return (RET_ERR);
		else if (r == RET_NOK)
		{
			ft_deq_shift(&self->srcs, NULL);
			continue ;
		}
		if ((r = lexer_scan_one(self, peek, src)) == RET_ERR)
			return (RET_ERR);
		if (r == RET_OK)
			++c;
	}
	return (c);
}
