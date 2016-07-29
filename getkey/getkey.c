#include <errno.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "my.h"
#define BUFSIZE 512

/*
** int ioctl(int d, unsigned long request, ...);
*/

void	getkey()
{
  int	nblu;
  char	buffer[BUFSIZE];/*a replace par un char */
  int	args;
  int	codeAscii;

  struct termios t;

  if (ioctl(0, TIOCGETA, &t) == -1)
    my_put_nbr_error(errno);
  t.c_lflag &= ~(ICANON | ECHO);
  /*t.c_cc[VMIN] = 1;*/
  if (ioctl(0, TIOCSETA, &t) == -1)
    my_put_nbr_error(errno);
  while ((nblu = read(0, buffer, BUFSIZE)) != 0)
    {
      if (nblu == -1)
	exit(-1);
      my_put_nbr(buffer[0]);
    }
}

int	main()
{
  getkey();
  return (0);
}
