/*
** storage.h for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:47:45 2016 Victor Gouet
** Last update Wed Feb 10 10:55:53 2016 Victor Gouet
*/

#ifndef STORAGE_H_
# define STORAGE_H_

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include "bits.h"

# define FLAGSNBR		(int)sizeof(FLAGSCHAR)
# define FLAGSCHAR		"sdBbc-rn"
# define STRING(str, ...)	get_string(str, __VA_ARGS__)

typedef struct	s_nstr
{
  unsigned int	n;
  char		*str;
}		t_nstr;

typedef struct	s_replace_occurence
{
  char		*str;
  char		*occurence;
  char		*with_string;
}		t_replace;

/*
** counts_size_bytes.c
*/

int	counts_size_bytes(char *format, va_list ap);

/*
** storage.c
*/

char	*get_string(char *format, ...);

/*
** controller_flags.c
*/

int	controller_flags_size(char c, va_list ap);
void	controller_flags_storage(char *str, va_list ap, int *i, char c);

/*
** on_flag_strings.c
*/

int	on_size_strings(va_list ap);
void	on_storage_strings(va_list ap, char *ptr, int *i);

/*
** on_flag_integer.c
*/

int	on_size_integer(va_list ap);
void	on_storage_integer(va_list ap, char *ptr, int *i);

/*
** on_flags_bits.c
*/

int	on_size_bits_integer(va_list ap);
void	on_storage_bits_integer(va_list ap, char *ptr, int *i);
void	on_storage_bits_char(va_list ap, char *ptr, int *i);
int	on_size_bits_char(va_list ap);

/*
** on_flag_char.c
*/

void	on_storage_char(va_list ap, char *ptr, int *i);
int	on_size_char(va_list ap);

/*
** on_flags_less.c
*/

void	on_storage_less(va_list ap, char *ptr, int *i);
int	on_size_less(va_list ap);

/*
** on_flag_reverse.c
*/

void	on_storage_reverse(va_list ap, char *ptr, int *i);
int	on_size_reverse(va_list ap);

/*
** on_flag_bounded.c
*/

void	on_storage_bounded(va_list ap, char *ptr, int *i);
int	on_size_bounded(va_list ap);

/*
** on_flag_replace_occurence.c
*/

void	on_storage_replace(va_list ap, char *ptr, int *i);
int	on_size_replace(va_list ap);

#endif /* !STORAGE_H_ */
