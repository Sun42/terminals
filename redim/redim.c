#include "my.h"
#include <ncurses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <signal.h>
#ifndef HAVE_NOT_TERMCAP_H
#include <termcap.h>
#else
char    *tgetstr();
#endif
#define RETSIGTYPE void

RETSIGTYPE      sigwinch();
char    *xtgetstr(char *cap, char **area);
void    my_outc(int c);

char    *getenv();

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

void    my_outc(int c)
{
  my_putchar(c);
}

RETSIGTYPE      sigwinch()
{
  struct winsize        w;

  if (ioctl(0, TIOCGWINSZ, &w) < 0)
    my_putstr("ioctl");
  my_putstr("ws_row=");
  my_put_nbr(w.ws_row);
  my_putstr("ws_col=");
  my_put_nbr(w.ws_col);
  my_putstr("\n");
}

int     main()
{
  char  *term;
  char  bp[1024];
  char  t[4096];
  char  *area;
  int   li;
  int   co;
  struct winsize        w;

  signal(SIGWINCH, sigwinch);
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
  if (ioctl(0, TIOCGWINSZ, &w) < 0)
    my_putstr("ioctl");
  area = t;
  li = tgetnum("li");
  co = tgetnum("co");
  my_putstr("ws_row=");
  my_put_nbr(w.ws_row);
  my_putstr("ws_col=");
  my_put_nbr(w.ws_col);
  my_putstr("\n");
  my_putstr("li=");
  my_put_nbr(li);
  my_putstr("co=");
  my_put_nbr(co);
  my_putstr("\n");
  while (1)
    pause();
}
