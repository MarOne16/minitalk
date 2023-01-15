/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:14:51 by mqaos             #+#    #+#             */
/*   Updated: 2023/01/09 19:33:30 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_counter;

int	ft_atoi(const char *str)
{
	int				x;
	unsigned int	z;
	int				i;

	x = 1;
	z = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		z *= 10;
		z += str[i] - '0';
		i++;
	}
	return (z * x);
}

void	bitcounter(int signal)
{
	if (signal == SIGUSR1)
		g_counter++;
}

void	handle(pid_t pid, int c, int digits)
{
	char	*binary;
	int		index;

	binary = malloc((digits) * sizeof(char));
	if (!binary)
		return ;
	index = digits - 1;
	while (index >= 0)
	{
		binary[index] = (c & 1) + '0';
		c >>= 1;
		if (binary[index] == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		index--;
		usleep(100);
		usleep(100);
	}
	free(binary);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid > 1)
		{
			while (argv[2][i])
			{
				signal(SIGUSR1, &bitcounter);
				handle(pid, argv[2][i], 8);
				i++;
			}
			ft_printf("total bytes: %d", g_counter);
		}
	}
	return (0);
}
