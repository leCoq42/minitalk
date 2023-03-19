/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:36:21 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/19 16:17:05 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

void	send_signal(pid_t PID, char c)
{
	int	b;

	ft_printf("%c\n", c);
	b = 0;
	while (b < 8)
	{
		if (c & 1)
			kill(PID, SIGUSR2);
		else
			kill(PID, SIGUSR1);
		c >>= 1;
		usleep(1000);
		b++;
	}
}

int	main(int argc, char *argv[])
{
	char	*str;

	if (argc < 3)
		return (1);
	str = argv[2];
	while (*str)
	{
		send_signal(ft_atoi(argv[1]), *str);
		str++;
	}
}
