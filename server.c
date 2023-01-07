/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:06:56 by mqaos             #+#    #+#             */
/*   Updated: 2023/01/07 22:38:22 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void sigint_handler(int sig, siginfo_t *info, void *context)
{
  static int  i;
  static int  b;
  static int  id;
  (void)context;
  if (id != info->si_pid)
	{
		b = 0;
		i = 0;
	}
	id = info->si_pid;
  if (sig == SIGUSR1)
    i  = i | 1 << b;
  b++;
  if (b == 8)
  {
    write(1,&i,1);
    i = 0;
    b = 0;
    kill(info->si_pid,SIGUSR1);
  }
}

int main(void)
{
  struct sigaction sa;
  int pid = getpid();
  printf("[%d]\n", pid);
  sa.sa_sigaction = &sigint_handler;
  while (1)
  {
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    pause();
  }
}
