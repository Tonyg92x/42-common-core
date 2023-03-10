/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classDog.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:58:34 by aguay             #+#    #+#             */
/*   Updated: 2022/09/29 09:00:27 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classDog.hpp"

Dog::Dog(void) : AAnimal(), brain(new Brain())
{
	std::cout << "Default Dog constructor called" << std::endl;
	this->_type = "Dog";
}

Dog::Dog(Dog const & rhs) : AAnimal(), brain(new Brain())
{
	std::cout << "Copy Dog constructor called" << std::endl;
	*this = rhs;
}

Dog::~Dog(void)
{
	delete this->brain;
	std::cout << "Default Dog destructor" << std::endl;
}

Dog &	Dog::operator=(Dog const & rhs)
{
	std::cout << "Dog operator overload = called" << std::endl;
	if (this != & rhs)
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

void	Dog::get_idea(size_t index)
{
	std::cout << this->brain->get_idea(index) << std::endl;
}