/*
** fork_process.c for fork_process in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Apr 11 17:17:06 2017 David Zeng
** Last update Tue Apr 11 17:17:06 2017 David Zeng
*/

#include "strace.h"

pid_t	fork_process(char *argv[])
{
  pid_t	pid;

  if ((pid = fork()) == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      exit(execvp(argv[0], argv));
    }
  else if (pid < 0)
    {
      fprintf(stderr, "fork error\n");
      exit(1);
    }
  return (pid);
}

pid_t	trace_process(pid_t pid)
{
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
      fprintf(stderr, "Attach error\n");
      exit(1);
    }
  return (pid);
}
