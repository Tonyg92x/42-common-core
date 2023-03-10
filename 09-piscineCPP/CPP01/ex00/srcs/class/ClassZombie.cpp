/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassZombie.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 09:52:26 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 10:18:34 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassZombie.hpp"

Zombie::Zombie(std::string name)
{
	set_name(name);
	return;
}

Zombie::~Zombie(void)
{
	return;
}

void	Zombie::set_name(std::string name)
{
	this->name = name;
}

std::string	Zombie::get_name(void)
{
	return (this->name);
}

void	Zombie::announce(void)
{
	std::cout << Zombie::get_name() << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
