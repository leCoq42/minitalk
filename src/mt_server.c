/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:30:16 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/24 18:07:21 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

static void	signal_handler(int sig, siginfo_t *info, ucontext_t *uap)
{
	static int				bit = 0;
	static unsigned char	c = 0x00;
	unsigned int			end;

	(void)uap;
	end = 0;
	if (sig == SIGUSR2)
		c |= 1 << bit;
	else if (sig == SIGUSR1)
		c |= 0 << bit;
	bit++;
	if (bit == 8)
	{
		if (c == 0x00)
		{
			ft_putchar_fd('\n', 1);
			end = 1;
		}
		else
			ft_putchar_fd(c, 1);
		bit = 0;
		c = 0x00;
	}
	if (!end)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
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
		pause();
	return (0);
}
