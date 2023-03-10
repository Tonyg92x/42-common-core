/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:42:52 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 15:15:45 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classAnimal.hpp"

//	Constructor's
AAnimal::AAnimal(void)
{
	std::cout << "Default Animal constructor called" << std::endl;
};

AAnimal::AAnimal(AAnimal const & rhs)
{
	std::cout << "Copy Animal contructor called" << std::endl;
	*this = rhs;
}

//	Destructor's
AAnimal::~AAnimal(void)
{
	std::cout << "Default Animal destructor called" << std::endl;
}

//	Operator overload's
AAnimal &	AAnimal::operator=(AAnimal const & rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs._type;
	}
	return (*this);
}

void	AAnimal::makeSound(void) const
{
	std::cout <<"Animal sound" << std::endl;
}

std::string	AAnimal::getType(void) const
{
	return (this->_type);
}
