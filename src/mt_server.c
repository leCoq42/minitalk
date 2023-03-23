/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:30:16 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/23 15:17:51 by mhaan         ########   odam.nl         */
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
	}
	if (bit >= 8)
	{
		if (c == 0x00)
		{
			ft_putchar_fd('\n', 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			ft_putchar_fd(c, 1);
			kill(info->si_pid, SIGUSR1);
		}
		bit = 0;
		c = 0x00;
	}
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	const char			*pid = ft_itoa(getpid());

	ft_putstr_fd("Server PID: ", 1);
	ft_putstr_fd((char *)pid, 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = (void *)signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
}
