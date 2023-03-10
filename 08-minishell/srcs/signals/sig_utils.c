/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:33:34 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 13:09:17 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(void)
{
	struct termios		termios_save;
	struct termios		termios_new;
	struct sigaction	action;

	tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_handler = sig_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
}

void	sig_chuttt(void)
{
	struct termios	termios_save;
	struct termios	termios_new;

	tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
