/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool/mark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/pool.h"

inline int		sh_poolmark(pid_t pid, int status)
{
	size_t	i;
	size_t	j;
	t_job	*job;
	t_proc	*proc;

	if (!g_pool)
		return (NOP);
	if (pid > 0)
	{
		i = 0;
		while (i < g_pool->len)
		{
			j = 0;
			job = g_pool->jobs + i++;
			while (j < job->procs.len)
				if ((proc = job->procs.buf + j++)->pid == pid)
				{
					sh_procmark(proc, status);
					if (job->bg == 0 && proc->status == PROC_STOPPED)
						job->bg = 1;
				}
		}
		return (NOP);
	}
	return ((pid == 0 || errno == ECHILD) ? WUT : THROW(WUT));
}
