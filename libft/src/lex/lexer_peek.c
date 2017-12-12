/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_peek.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 11:21:55 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline int			ft_lexer_peek(t_lexer *self, size_t n, t_tok **peek)
{
	ssize_t sz;

	if (ft_deq_size(&self->toks) < n + 1 &&
		(sz = ft_lexer_scan(self, n + 1)) < (ssize_t)n + 1)
		return (sz <= 0 ? (int)sz : NOP);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, n);
	return (YEP);
}

inline ssize_t		ft_lexer_next(t_lexer *self, size_t n, t_tok **peek)
{
	ssize_t sz;

	if (ft_deq_size(&self->toks) < n && (sz = ft_lexer_scan(self, n)) <= 0)
		return (sz);
	if (peek)
		*peek = (t_tok *)ft_deq_at(&self->toks, 0);
	return (ft_deq_shiftn(&self->toks, n, NULL));
}

inline size_t		ft_lexer_skip(t_lexer *self, size_t n, t_tok **out)
{
	return (ft_deq_shiftn(&self->toks, n, out));
}

inline int			ft_lexer_match(t_tok *tok, t_src *src, size_t n, uint8_t id)
{
	ssize_t sz;

	tok->id = id;
	tok->val = NULL;
	if ((sz = ft_src_next(src, NULL, n)) <= 0)
		return ((int)sz);
	return (YEP);
}
