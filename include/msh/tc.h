/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/tc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TC_H
# define MSH_TC_H

# include <libft.h>

# define K_RETURN		"\xa"
# define K_BACKSPACE	"\x7f"
# define K_DEL			"\x1b\x5b\x33\x7e"
# define K_CTRL_U		"\x15"
# define K_CTRL_D		"\x4"
# define K_CTRL_A		"\x1"
# define K_CTRL_E		"\x5"
# define K_CTRL_R		"\x12"
# define K_CTRL_L		"\xc"
# define K_CTRL_K		"\xb"
# define K_CTRL_P		"\x10"
# define K_ALT_B		"\x1b\x62"
# define K_ALT_F		"\x1b\x66"
# define K_UP			"\x1b\x5b\x41"
# define K_DOWN			"\x1b\x5b\x42"
# define K_RIGHT		"\x1b\x5b\x43"
# define K_LEFT			"\x1b\x5b\x44"
# define K_CTRL_UP		"\x1b\x5b\x31\x3b\x35\x41"
# define K_CTRL_DOWN	"\x1b\x5b\x31\x3b\x35\x42"
# define K_CTRL_RIGHT	"\x1b\x5b\x31\x3b\x35\x43"
# define K_CTRL_LEFT	"\x1b\x5b\x31\x3b\x35\x44"

# ifdef LINUX
#  define K_START		"\x1b\x4f\x48"
#  define K_END			"\x1b\x4f\x46"
#  define K_CTRL_Y		"\x19"
# else
#  define K_START		K_CTRL_A
#  define K_END			K_CTRL_E
#  define K_CTRL_Y		"\x8"
# endif

typedef TTY		t_tcios;

struct s_tc;

typedef int		(*t_tc_hook)(struct s_tc *self, char *ch);

typedef struct	s_tc
{
	t_tcios		curr;
	t_tcios		prev;
	void		*arg;
	int			tty;
	int			col;
	int			row;
	int			sx;
	int			sy;
	int			x;
	int 		y;
	t_dstr		in;
	t_du8		r;
}				t_tc;

extern char		*g_tcaps[];

extern int		tc_ctor(t_tc *self, char **env, void *arg);
extern void		tc_dtor(t_tc *self);
extern void		tc_pause(t_tc *self);
extern void		tc_resume(t_tc *self);
extern int		tc_register(t_tc *self);
extern int		tc_putc(t_tc *self, char c);
extern int		tc_puts(t_tc *self, char const *s);
extern int		tc_putnl(t_tc *self, char const *s);
extern int		tc_insc(t_tc *self, char c);
extern int		tc_inss(t_tc *self, char const *s);
extern int		tc_clrln(t_tc *self);
extern int		tc_clr(t_tc *self);
extern int		tc_left(t_tc *self);
extern int		tc_margin_left(t_tc *self);
extern int		tc_right(t_tc *self);
extern int		tc_up(t_tc *self);
extern int		tc_down(t_tc *self);
extern int		tc_loop(t_tc *self, t_tc_hook hook);

#endif
