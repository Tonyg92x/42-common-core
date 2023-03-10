/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classClapTrap.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 08:23:42 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 11:37:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classClapTrap.hpp"

//	Constructor's

ClapTrap::ClapTrap(void) : _name("undefined"), _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
	std::cout << "Defaul constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
	std::cout << "Constructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const & rhs)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = rhs;
}

//	Destructor
ClapTrap::~ClapTrap(void)
{
	std::cout << "Destructor called" << std::endl;
}

//	Operator overload

//	If the reference != this, change all variable's to rhs variable's
ClapTrap & ClapTrap::operator=(ClapTrap const & rhs)
{
	std::cout << "Operator overload assignation called" << std::endl;
	if (&rhs != this)
	{
		_name = rhs.getName();
		_hitPoint = rhs.getHitPoint();
		_energyPoint = rhs.getEnergyPoint();
		_attackDamage = rhs.getAttackDamage();
	}
	return (*this);
}

//	Object method's

void	ClapTrap::attack(const std::string& target)
{
	if (this->_energyPoint > 0 && this->_hitPoint > 0)
	{
		std::cout << ClapTrap::getName() << " attack " << target;
		std::cout << " for " << ClapTrap::getAttackDamage() << " damage." << std::endl;
		_energyPoint--;
	}
	else if (this->_energyPoint == 0)
		std::cout << ClapTrap::getName() << " : zzzzzzzzzzz" << std::endl;
	else
		std::cout <<ClapTrap::getName() << " is dead." << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hitPoint == 0)
	{
		std::cout << ClapTrap::getName() << " is dead." << std::endl;
		return ;
	}
	if (amount >= this->_hitPoint)
	{
		std::cout << ClapTrap::getName() << " take " << amount << " damage! It's fatal." << std::endl;
		this->_hitPoint = 0;
		this->_energyPoint = 0;
		return;
	}
	std::cout << ClapTrap::getName() << " take " << amount << " damage!" << std::endl;
	this->_hitPoint -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_energyPoint > 0 && this->_hitPoint > 0)
	{
		this->_hitPoint += amount;
		std::cout << ClapTrap::getName() << " got repaired for " << amount << std::endl;
		_energyPoint--;
	}
	else if (ClapTrap::getHitPoint() == 0)
		std::cout << this->_name << " is dead." << std::endl;
	else
		std::cout << this->_name << " : zzzzzzzzzzz" << std::endl;
		
}

//	Getter's

std::string	ClapTrap::getName(void) const {return this->_name;}

unsigned int	ClapTrap::getHitPoint(void) const {return this->_hitPoint;}

unsigned int	ClapTrap::getEnergyPoint(void) const {return this->_energyPoint;}

unsigned int	ClapTrap::getAttackDamage(void) const {return this->_attackDamage;}
