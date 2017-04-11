/*
** main.c for main in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Mon Jan 23 17:57:49 2017 David Zeng
** Last update Mon Jan 23 17:57:49 2017 David Zeng
*/

#include "strace.h"

static pid_t	g_pid = -1;

void		handle_sig(int sig)
{
  if (sig == SIGINT && g_pid != -1)
    {
      ptrace(PTRACE_DETACH, g_pid, NULL, NULL);
    }
}

int		main(int argc, char *argv[])
{
  t_param	param;
  pid_t		pid;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s [-s] [-p <pid>|<command>]\n", argv[0]);
      exit(1);
    }
  param = parse_args(argc, argv);
  if (!param.p)
    {
      pid = fork_process(param.argv);
    }
  else
    {
      pid = trace_process(param.pid);
      g_pid = pid;
    }
  trace_syscall(pid);
  return (0);
}
