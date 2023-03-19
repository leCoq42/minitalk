/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:30:16 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/19 16:16:20 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "0\n", 2);
	}
	else if (sig == SIGUSR2)
	{
		write(1, "1\n", 2);
	}
}

int	main(void)
{
	struct sigaction	sa;
	const char			*pid = ft_itoa(getpid());

	write(1, "Server PID: ", 12);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		continue ;
}
