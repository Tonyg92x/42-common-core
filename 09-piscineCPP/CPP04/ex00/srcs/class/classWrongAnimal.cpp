/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classWrongAnimal.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:36:08 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 13:53:21 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classWrongAnimal.hpp"
//	Constructor's

WrongAnimal::WrongAnimal(void)
{
	std::cout << "Default WrongAnimal constructor called" << std::endl;
};

WrongAnimal::WrongAnimal(WrongAnimal const & rhs)
{
	std::cout << "Copy WrongAnimal contructor called" << std::endl;
	*this = rhs;
}

WrongAnimal::WrongAnimal(std::string type) : _type(type)
{
	std::cout << "WrongAnimal constructor with type initialised" << std::endl;
}

//	Destructor's
WrongAnimal::~WrongAnimal(void)
{
	std::cout << "Default WrongAnimal destructor called" << std::endl;
}

//	Operator overload's
WrongAnimal &	WrongAnimal::operator=(WrongAnimal const & rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs._type;
	}
	return (*this);
}

void	WrongAnimal::makeSound(void) const
{
	std::cout <<"WrongAnimal sound" << std::endl;
}

std::string	WrongAnimal::getType(void) const
{
	return (this->_type);
}
