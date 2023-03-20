/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:30:16 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/20 17:23:52 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

static void	signal_handler(int sig, siginfo_t *info, ucontext_t *uap)
{
	static int				bit = 0;
	static unsigned char	c = 0x00;

	(void)uap;
	if (bit < 8)
	{
		if (sig == SIGUSR2)
			c |= 0x01 << bit;
		bit++;
		kill(info->si_pid, SIGUSR1);
	}
	if (bit == 8)
	{
		if (c == 0x00)
			kill(info->si_pid, SIGUSR2);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0x00;
	}
}

int	main(void)
{
	struct sigaction	sa;
	const char			*pid = ft_itoa(getpid());

	write(1, "Server PID: ", 12);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	sa.sa_sigaction = (void *)signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
