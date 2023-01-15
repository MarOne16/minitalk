/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:18:16 by mqaos             #+#    #+#             */
/*   Updated: 2023/01/10 15:05:48 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sigint_handler(int sig, siginfo_t *sinf, void *context)
{
	static int	i;
	static int	b;
	static int	id;

	(void)context;
	if (id != sinf->si_pid)
	{
		b = 0;
		i = 0;
	}
	id = sinf->si_pid;
	if (sig == SIGUSR1)
		i = i | 1 << b;
	b++;
	if (b == 8)
	{
		write(1, &i, 1);
		i = 0;
		b = 0;
		kill(sinf->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("[%d]\n", getpid());
	sa.sa_sigaction = &sigint_handler;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}
