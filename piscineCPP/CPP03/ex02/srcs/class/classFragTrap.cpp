/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFragTrap.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 07:38:25 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 11:37:37 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classFragTrap.hpp"

//	Constructor's
FragTrap::FragTrap(void) : ClapTrap()
{
	std::cout << "Default FragTrap constructor called" << std::endl;
	this->_attackDamage = 30;
	this->_hitPoint = 100;
	this->_energyPoint = 100;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << name << " FragTrap constructor called" << std::endl;
	this->_attackDamage = 30;
	this->_hitPoint = 100;
	this->_energyPoint = 100;
}

FragTrap::FragTrap(FragTrap const & rhs) : ClapTrap(rhs.getName())
{
	std::cout << "FragTrap copy contructor called" << std::endl;
	*this = rhs;
}

//	Destructor's
FragTrap::~FragTrap(void)
{
	std::cout << this->getName() << " Default destructor called" << std::endl;
}

//	Overload operator's
FragTrap & FragTrap::operator=(FragTrap const & rhs)
{
	std::cout << rhs.getName() << " copy operator overlaod called" << std::endl;
	if (&rhs != this)
	{
		this->_name = rhs.getName();
		this->_attackDamage = rhs.getAttackDamage();
		this->_energyPoint = rhs.getEnergyPoint();
		this->_attackDamage = rhs.getAttackDamage();
	}
	return (*this);
}

//	Methods
void	FragTrap::highFivesGuys(void)
{
	std::cout << this->getName() << ": Heeeeyyyy... High five guys ?" << std::endl;
}
