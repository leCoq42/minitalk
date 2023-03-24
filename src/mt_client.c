/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:36:21 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/24 17:51:30 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk.h"

int	g_rdy = 1;

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
			while (!g_rdy)
				;
			if (str[i] >> bit & 1)
				kill(PID, SIGUSR2);
			else
				kill(PID, SIGUSR1);
			g_rdy = 0;
			bit++;
		}
		i++;
	}
	end_message(PID, max_bits);
}

static void	end_message(pid_t PID, const int max_bits)
{
	int	i;

	i = 0;
	while (i < max_bits)
	{
		while (!g_rdy)
			;
		kill(PID, SIGUSR1);
		g_rdy = 0;
		i++;
	}
}

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_rdy = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Server: message received!\n", 1);
		g_rdy = 0;
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	const pid_t			pid = ft_atoi(argv[1]);

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	if (argc != 3)
	{
		ft_putstr_fd("Error. Usage: ./client <server_PID> <string to send>\n", 2);
		exit (EXIT_FAILURE);
	}
	if (kill(pid, 0) == -1)
	{
		ft_putstr_fd("ERROR: invalid PID!\n", 2);
		exit (EXIT_FAILURE);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
