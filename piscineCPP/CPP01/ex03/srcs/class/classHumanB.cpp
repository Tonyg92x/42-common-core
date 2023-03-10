/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classHumanB.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:26:36 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 13:08:01 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classHumanB.hpp"

HumanB::HumanB(std::string name) : name(name), arme(NULL)
{
	return ;
}

HumanB::~HumanB(void)
{
	return ;
}

void	HumanB::attack(void)
{
	std::cout << this->name << " attack with their ";
	if (this->arme)
		std::cout << (*this->arme).getType() << std::endl;
	else
		std::cout << "fist" << std::endl;
	return ;
}

std::string	HumanB::getName(void)
{
	return (this->name);
}

Weapon	HumanB::getWeapon(void)
{
	return (*this->arme);
}

void	HumanB::setWeapon(Weapon& arme)
{
	this->arme = &arme;
}
