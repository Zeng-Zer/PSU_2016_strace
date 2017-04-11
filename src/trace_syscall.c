/*
** trace_syscall.c for trace_syscall in /home/zeng_d
**
** Made by David Zeng
** Login   <zeng_d@epitech.net>
**
** Started on  Tue Apr 11 17:03:01 2017 David Zeng
** Last update Tue Apr 11 17:03:01 2017 David Zeng
*/

#include "strace.h"

static void			print_syscall(struct user_regs_struct *regs)
{
  fprintf(stderr, "syscall %s\n", get_syscall_name(regs->rax));
}

void				trace_syscall(pid_t pid)
{
  int				status;
  short				rip;
  struct user_regs_struct	regs;

  while (waitpid(pid, &status, 0) && !WIFEXITED(status))
    {
      ptrace(PTRACE_GETREGS, pid, NULL, &regs);
      rip = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, NULL);
      if (rip == SYSCALL)
	{
	  print_syscall(&regs);
	}
      ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    }
}
