/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:36:21 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/20 17:08:55 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

int	g_rdy = 1;

static void	send_signal(pid_t PID, char c)
{
	int			b;
	const int	max_bits = 8;

	b = 0;
	while (b < (max_bits))
	{
		while (!g_rdy)
			pause();
		if (c >> b & 1)
			kill(PID, SIGUSR2);
		else
			kill(PID, SIGUSR1);
		g_rdy = 0;
		b++;
	}
}

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_rdy = 1;
	else if (sig == SIGUSR2)
		write(1, "Server received message!\n", 25);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
		exit (EXIT_FAILURE);
	while (*argv[2])
	{
		send_signal(ft_atoi(argv[1]), *argv[2]);
		argv[2]++;
	}
	send_signal(ft_atoi(argv[1]), *argv[2]);
	pause();
}
