/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classHumanA.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:12:12 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 12:54:02 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classHumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon& gun) : arme(gun), name(name)
{
	return;
}

HumanA::~HumanA(void)
{
	return ;
}

void	HumanA::attack(void)
{
	std::cout << this->name << " attack with their " << this->arme.getType() << std::endl;
	return ;
}

std::string	HumanA::getName(void)
{
	return (this->name);
}

Weapon	HumanA::getWeapon(void)
{
	return (this->arme);
}
