/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:30:16 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/18 18:11:20 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"


void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "SIGUSR1 received\n", 17);
	}
	else if (sig == SIGUSR2)
	{
		write(1, "SIGUSR2 received\n", 17);
	}
}


int	main(void)
{
	pid_t	PID;
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	PID = getpid();
	printf("Server PID:%i\n", PID);
	pause();
}