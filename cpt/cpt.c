#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include <curses.h>
#include <ncurses.h>
#include <term.h>
#ifndef HAVE_NOT_TERMCAP_H
#include <termcap.h>
#else
char    *tgetstr();
#endif

void    my_outc(int c)
{
  my_putchar(c);
  
}


char    *xtgetstr(char *cap, char **area)
{
  char  *capstr;
  
  if ((capstr = tgetstr(cap, area)) == NULL)
    {
      my_putstr("problem getting ");
      my_putstr(cap);
      my_putchar('\n');
      exit(1);
    }
  return (capstr);
}

int	xgetnum(char	*cap)
{
  int capnum;

  if ((capnum = tgetnum(cap)) == -1)
    {
      my_putstr("problem getting ");
      my_putstr(cap);
      my_putchar('\n');
      exit(1);
    }
  return (capnum);
}

void	cpt()
{
  char  *term;
  char  bp[1024];
  char  t[4096];
  char  *area;
  char  *clstr; /* Clear */
  char  *sostr; /* StandOut */
  char  *sestr; /* Standout End */
  char  *cmstr; /* Cursor Motion */
  char	*lestr;

  int   x;
  int   y;
  int	i;

  i = 0;
  if ((term = getenv("TERM")) == NULL)
    {
      my_putstr("can't determine terminal\n");
      exit(1);
    }
  if (tgetent(bp, term) != 1)
    {
      my_putstr("problem with tgetent\n");
      exit(1);
    }
  area = t;
  cmstr = xtgetstr("cm", &area);
  clstr = xtgetstr("cl", & area);
  lestr = xtgetstr("le",  &area);
  tputs(clstr, 1, my_outc);
  /*
    my_putstr(cmstr);
    my_putchar('\n');
  */
  x = 0;
  y = 0;
  while (i < 15)
    {
      /*char *tgoto(const char *cap, int col, int row);*/
      /* int tputs(const char *str, int affcnt, int (*putc)(int));*/
      my_put_nbr(i);
      sleep(1);
      tputs(tgoto(cmstr, x, y), 1, my_outc);
      /*tputs(lestr, 1 , my_outc);*/

      /*tgoto(cmstr, );*/
      i++;
    }
}

int	main()
{
  cpt();
  return (0);
}
