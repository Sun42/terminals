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


void	clearscreen()
{
  char  *term;
  char  bp[1024];
  char  t[4096];
  char  *area;
  char  *clstr; /* Clear */
  char  *sostr; /* StandOut */
  char  *sestr; /* Standout End */
  char  *cmstr; /* Cursor Motion */
  int   x;
  int   y;

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
  clstr = xtgetstr("cl", &area);
  sostr = xtgetstr("so", &area);
  sestr = xtgetstr("se", &area);
  cmstr = xtgetstr("cm", &area);
  my_putstr(clstr);
}

int	main()
{
  clearscreen();
  return (0);
}
