/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classHarl.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:40:34 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 13:14:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classHarl.hpp"


Harl::Harl(void)
{
	fonctionPtr[0] = &Harl::debug;
	levels[0] = "DEBUG";

	fonctionPtr[1] = &Harl::info;
	levels[1] = "INFO";

	fonctionPtr[2] = &Harl::warning;
	levels[2] = "WARNING";

	fonctionPtr[3] = &Harl::error;
	levels[3] = "ERROR";
	return ;
}

Harl::~Harl(void)
{
	return ;
}

int	Harl::getLevelCode(std::string level)
{
	for (int x = 0; x < 4; x++)
	{
		if (level == levels[x])
			return (x);
	}
	return (1000);
}

void	Harl::complain(std::string level)
{
	(this->*fonctionPtr[Harl::getLevelCode(level)])();
}

void	Harl::debug(void)
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
	return ;
}

void	Harl::info(void)
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
	return ;
}

void	Harl::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
	return ;
}

void	Harl::error(void)
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
	return ;
}