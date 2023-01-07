/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:07:56 by mqaos             #+#    #+#             */
/*   Updated: 2023/01/07 22:37:27 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


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

int counter;

void	bitcounter(int signal)
{
	if (signal == SIGUSR1)
		counter++;
}

void  handle(pid_t pid, int c,int digits)
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
int main(int argc, char* argv[]) {
  pid_t pid = ft_atoi(argv[1]);
  int i = 0;
  if (argc == 3)
  {
  while (argv[2][i])
  {
	signal(SIGUSR1,&bitcounter);
    handle(pid,argv[2][i],8);
    i++;
  }
	ft_printf("total bayts : %d",counter);
  }
  return 0;
}
