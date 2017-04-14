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

static void	print_syscall(t_proc *proc)
{
  fprintf(stderr, "%s", get_syscall_name(proc->regs.rax));
}

static void	print_param(t_proc *proc)
{
  int	i;

  i = get_syscall_number_params(proc->regs.rax);
  if (i == -1) {
    return ;
  }
  fprintf(stderr, "(");
  if (i-- > 0)
    fprintf(stderr, "0x%llx", proc->regs.rdi);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.rsi);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.rdx);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.r10);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.r8);
  if (i-- > 0)
    fprintf(stderr, ", 0x%llx", proc->regs.r9);
  fprintf(stderr, ")");
}

static void	print_ret(t_proc *proc)
{
  ptrace(PTRACE_SINGLESTEP, proc->pid, NULL, NULL);
  waitpid(proc->pid, &proc->status, 0);
  ptrace(PTRACE_GETREGS, proc->pid, NULL, &proc->regs);
  fprintf(stderr, " = 0x%llx\n", proc->regs.rax);
}

void		trace_syscall(pid_t pid, t_param param)
{
  t_proc	proc;

  proc.pid = pid;
  proc.param = param;
  while (waitpid(pid, &proc.status, 0) && !WIFEXITED(proc.status))
    {
      ptrace(PTRACE_GETREGS, pid, NULL, &proc.regs);
      if ((short)ptrace(PTRACE_PEEKTEXT, pid, proc.regs.rip, NULL) == SYSCALL)
	{
	  print_syscall(&proc);
	  print_param(&proc);
	  print_ret(&proc);
	}
      ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    }
}
