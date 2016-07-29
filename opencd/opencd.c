#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void	aff_err(char *str)
{
  my_putstr("Error: ");
  my_putstr(str);
  my_putchar('\n');
  exit(1);
}

int     main(int argc, char **argv)
{
  int   d;
  int   arg;

  if (argc != 2)
    {
      my_putstr("usage: my_eject special_file\n");
      exit(1);
    }
  if ((d = open(argv[1], O_RDONLY)) == -1)
    aff_err(argv[1]);
  if (ioctl(d, DIOCEJECT, &arg) == -1)
    aff_err("ioctl DIOEJECT");
  close(d);
}
