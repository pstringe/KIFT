/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:31:04 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/25 13:01:39 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <assert.h>
# include <wchar.h>
# define MAX 16000
# define TYPES "sSpdDioOuUxXcC%"
# define FLAGS "-+ 0#"
# define NO_OF_TYPES (14 + 1)
# define NO_OF_LENS 6

/*
**	define flags
*/

# define MINUS	1
# define PLUS	(1 << 1)
# define SPACE	(1 << 2)
# define ZERO	(1 << 3)
# define HASH	(1 << 4)

/*
**	define structs
*/

typedef struct	s_f
{
	int		m;
	int		p;
	int		s;
	int		z;
	int		h;
}				t_f;

typedef	struct	s_w
{
	struct s_num	*n;
	char			*w;
	int				z;
	int				l;
	int				e_char;
}				t_w;

typedef struct	s_num
{
	int		base;
	int		sign;
	int		idx;
	char	b_conv[100];
	int		neg;
	int		arg;
	int		p_len;
	int		w_len;
}				t_num;

typedef struct	s_p
{
	int				start;
	unsigned char	flags;
	int				width;
	int				precision;
	int				len;
	int				type;
}				t_p;

typedef	struct	s_m
{
	const char	*format;
	int			pos_f;
	int			pos_b;
	va_list		ap;
	struct s_p	*place;
}				t_m;

/*
**	main function
*/

int				ft_printf(const char *str, ...);

/*
**	functions essential for the main operation of printf
*/

int				cpy(t_m *m, char buf[MAX]);
int				get_placeholder(t_m *m);
int				convert(t_m *m, char buf[MAX]);

/*
**	initialization functions
*/

void			init_f(t_f *flags, t_m *m);
void			init_funcs(int	(*con[NO_OF_TYPES])(t_m*, char buf[MAX]));
void			init_lens(char	*lens[NO_OF_LENS]);
void			init(t_m *m, const char *format, char buf[MAX]);

/*
**	placeholder parsing functions
*/

int				get_width(t_m *m);
int				get_flags(t_m *m);
int				get_precision(t_m *m);
int				get_len(t_m *m);
int				get_type(t_m *m);

/*
**	conversion functions
*/

int				str(t_m *m, char buf[MAX]);
int				wstr(t_m *m, char buf[MAX]);
int				poi(t_m *m, char buf[MAX]);
int				dig(t_m *m, char buf[MAX]);
int				oct(t_m *m, char buf[MAX]);
int				usi(t_m *m, char buf[MAX]);
int				hex(t_m *m, char buf[MAX]);
int				uch(t_m *m, char buf[MAX]);
int				uni(t_m *m, char buf[MAX]);
int				chr(t_m *m, char buf[MAX]);
int				not(t_m *m, char buf[MAX]);

/*
**	functions needed to extract and prepare number arguments
*/

void			get_num(t_m *m, t_num *n);
void			unsigned_conversion(t_m *m, t_num *n);
void			signed_conversion(t_m *m, t_num *n);
void			get_base(t_m *m, t_num *n);
int				get_echar(t_num *n, t_w *spec, int flags);
int				get_signchar(t_num *n, int flags);
/*
**	functions for applying modifications to num strings
*/

int				get_echar(t_num *n, t_w *spec, int flags);
int				get_signchar(t_num *n, int flags);
void			num_prcs(t_num *n, int pr);
void			num_wdth(t_m *m, t_num *n, int wd, int flags);
void			append(t_num *n, t_w *spec, int wd, int flags);
void			prepend(t_num *n, t_w *spec, int wd, int flags);
void			flags(t_m *m, t_num *n);

/*
**	functions for converting numbers to strings
*/

void			ft_spn(intmax_t nb, t_num *n, t_m *m);
void			ft_upn(uintmax_t nb, t_num *n, t_m *m);

/*
**	misc functions for checking, output, cleanup ect ...
*/

void			skip_whitespace(t_m *m);
int				replace(t_m *m, char buf[MAX], char *conv);
int				is_flag(char c);
void			put(t_m *m, char buf[MAX]);
void			dstry(t_m *m);

#endif
