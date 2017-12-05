/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/bi.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BI_H
# define MSH_BI_H

# include "exe.h"

extern t_job_fn	sh_bi(char *exe);
extern t_st		sh_bi_echo(t_sh *sh, int ac, char **av, char **env);
extern t_st		sh_bi_cd(t_sh *sh, int ac, char **av, char **env);
extern t_st		sh_bi_setenv(t_sh *sh, int ac, char **av, char **env);
extern t_st		sh_bi_unsetenv(t_sh *sh, int ac, char **av, char **env);
extern t_st		sh_bi_env(t_sh *sh, int ac, char **av, char **env);
extern t_st		sh_bi_exit(t_sh *sh, int ac, char **av, char **env);

#endif
