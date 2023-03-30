/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:36:21 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/30 10:36:43 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

int	g_rdy = 0;

static void	send_message(pid_t PID, char *str);
static void	end_message(pid_t PID, const int max_int);
static void	signal_handler(int sig);

static void	send_message(pid_t PID, char *str)
{
	int				bit;
	unsigned int	i;
	const int		max_bits = 8;

	i = 0;
	while (str[i])
	{
		bit = 0;
		while (bit < max_bits)
		{
			if (str[i] >> bit & 1)
				mt_send_signal(PID, SIGUSR2);
			else
				mt_send_signal(PID, SIGUSR1);
			bit++;
			while (!g_rdy)
				;
			g_rdy = 0;
		}
		i++;
	}
	end_message(PID, max_bits);
}

static void	end_message(pid_t PID, const int max_bits)
{
	int	bit;

	bit = 0;
	while (bit < max_bits)
	{
		mt_send_signal(PID, SIGUSR1);
		bit++;
		while (!g_rdy)
			;
		g_rdy = 0;
	}
	ft_putstr_fd("Server: message received!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_rdy = 1;
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	signal(SIGUSR1, signal_handler);
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <server_PID> <string_to_send>\n", \
						STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1 || kill(pid, 0) == -1)
	{
		ft_putstr_fd("ERROR: invalid PID!\n", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
