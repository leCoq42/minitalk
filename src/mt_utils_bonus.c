/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mt_utils_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 16:53:31 by mhaan         #+#    #+#                 */
/*   Updated: 2023/03/29 17:07:20 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"mini_talk_bonus.h"

void	mt_send_signal(pid_t PID, int sig)
{
	if (kill(PID, sig) == -1)
	{
		ft_putstr_fd("Error sending signal.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
