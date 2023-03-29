/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_server_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 16:53:44 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/29 17:07:14 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk_bonus.h"

static void	signal_handler(int sig, siginfo_t *info, ucontext_t *uap);
static void	write_char(unsigned char c);

static void	signal_handler(int sig, siginfo_t *info, ucontext_t *uap)
{
	static int				bit = 0;
	static unsigned char	c = 0;

	(void)uap;
	if (sig == SIGUSR2)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write_char(c);
		bit = 0;
		c = 0;
	}
	mt_send_signal(info->si_pid, SIGUSR1);
}

static void	write_char(unsigned char c)
{
	if (c == '\0')
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
		ft_putchar_fd(c, STDOUT_FILENO);
}

int	main(void)
{
	struct sigaction	sa;
	const char			*pid = ft_itoa(getpid());

	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putstr_fd((char *)pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	sa.sa_sigaction = (void *)signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
