/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

#define N_UNSET COLOR_RED COLOR_BOLD "unsetenv: " COLOR_RESET

inline int	sh_biunsetenv(int ac, char **av, char **env)
{
	int i;
	int fst;

	(void)env;
	if (ac < 2)
		return (ft_retf(NOP, N_UNSET"%e\n", EINVAL));
	i = 0;
	fst = YEP;
	while (++i < ac)
		if (ft_strchr(av[i], '='))
			return (ft_retf(NOP, N_UNSET"%s\n", "Syntax error"));
		else if (!sh_unsetenv(av[i], 1))
			ft_retf((fst = NOP), N_UNSET"%s: Environ not fount\n",
				av[i]);
	return (fst);
}
