/*
** parse_args.c for parse_args in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Mar  7 01:39:10 2017 David Zeng
** Last update Tue Mar  7 01:39:10 2017 David Zeng
*/

#include "strace.h"

static void	usage_exit(char *prog)
{
  fprintf(stderr, "usage: %s [-s] [-p <pid>|<command>]\n", prog);
  exit(1);
}

static int	compute_opt(char c, t_param *param)
{
  char		*next;

  if (c == 's')
    param->s = true;
  else if (c == 'p')
    {
      param->p = true;
      param->pid = strtol(optarg, &next, 10);
      if (next == optarg || *next != '\0')
	{
	  fprintf(stderr, "expected valid number after -%c\n", c);
	  return (1);
	}
    }
  else
    return (1);
  return (0);
}

t_param		parse_args(int argc, char *argv[])
{
  t_param	param;
  int		c;

  bzero(&param, sizeof(t_param));
  while ((c = getopt(argc, argv, "sp:")) != -1)
    {
      if (compute_opt(c, &param) == 1)
	usage_exit(argv[0]);
    }
  if (argv[optind])
    {
      param.argv = &argv[optind];
      param.argc = argc - optind;
    }
  if ((!param.p && param.argc == 0) || (param.p && param.argc != 0))
    usage_exit(argv[0]);
  return (param);
}
