/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classDog.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:58:34 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 13:53:29 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classDog.hpp"

Dog::Dog(void) : AAnimal("Dog")
{
	std::cout << "Default Dog constructor called" << std::endl;
	this->_type = "Dog";
}

Dog::Dog(Dog const & rhs) : AAnimal("Dog")
{
	std::cout << "Copy Dog constructor called" << std::endl;
	*this = rhs;
}

Dog::~Dog(void)
{
	std::cout << "Default Dog destructor" << std::endl;
}

Dog &	Dog::operator=(Dog const & rhs)
{
	std::cout << "Dog operator overload = called" << std::endl;
	this->_type = rhs._type;
	return (*this);
}

void	Dog::makeSound(void) const
{
	std::cout << "Wooof" << std::endl;
}

std::string	Dog::getType(void) const
{
	return (this->_type);
}
