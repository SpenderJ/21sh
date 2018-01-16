/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

inline int			sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	size_t	eofl;

	eofl = tok->len;
	eof = ft_memcpy(ft_malloc(eofl * sizeof(char)), tok->val, tok->len);
	tok->len = 0;
	while (1)
		if (!**it && (fd < 0 || !(*it = rl_catline(fd, "> ", 0, ln))))
			return (sh_synerr(*ln, *it, "Unexpected "
				"EOF while looking for heredoc delimiter `%s'", eof));
		else if (*it == (char *)-1)
			return (WUT);
		else if (*ft_sdscpush((t_sds *)tok, *(*it)++) == '\n' && tok->len >=
			eofl + 2 && tok->val[tok->len - (eofl + 2)] == '\n' &&
			!ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
		{
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	free(eof);
	return (YEP);
}

inline int			sh_lexheredoct(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	size_t	eofl;

	eofl = tok->len;
	eof = ft_memcpy(ft_malloc(eofl * sizeof(char)), tok->val, tok->len);
	tok->len = 0;
	while (1)
	{
		if (!**it && (fd < 0 || !(*it = rl_catline(fd, "> ", 0, ln))))
			return (*it == (char *)-1 ? WUT : sh_synerr(*ln, *it, "Unexpected "
				"EOF while looking for heredoc delimiter `%s'", eof));
		if (*(*it - 1) == '\n')
			while (**it == '\t')
				++*it;
		if (*ft_sdscpush((t_sds *)tok, *(*it)++) == '\n' && tok->len >=
			eofl + 2 && tok->val[tok->len - (eofl + 2)] == '\n' &&
			!ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
		{
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	}
	free(eof);
	return (YEP);
}