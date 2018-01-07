/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/shell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SHELL_H
# define MSH_SHELL_H

# include "tokenize.h"

extern t_bool	g_shinteract;
extern pid_t	g_shpgid;
extern TTY		g_rawmode;

extern int		sh_launch(int fd);
extern int		sh_exit(int exitno, char const *fmt, ...);

#endif
