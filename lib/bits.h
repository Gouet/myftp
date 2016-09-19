/*
** bits.h for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:47:37 2016 Victor Gouet
** Last update Wed Feb 10 10:47:38 2016 Victor Gouet
*/

#ifndef BITS_H_
# define BITS_H_

typedef struct	s_bits
{
  unsigned char	h : 1;
  unsigned char	g : 1;
  unsigned char	f : 1;
  unsigned char	e : 1;
  unsigned char	d : 1;
  unsigned char	c : 1;
  unsigned char	b : 1;
  unsigned char	a : 1;
}		t_bits;

typedef union	s_integer
{
  t_bits	bits[4];
  int		value;
}		t_integer;

#endif /* !BITS_H_ */
