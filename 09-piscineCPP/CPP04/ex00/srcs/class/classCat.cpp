/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:16:45 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 13:53:32 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classCat.hpp"

Cat::Cat(void) : AAnimal("Cat")
{
	std::cout << "Default Cat constructor called" << std::endl;
	this->_type = "Cat";
}

Cat::Cat(Cat const & rhs) : AAnimal("Cat")
{
	std::cout << "Copy Cat constructor called" << std::endl;
	*this = rhs;
}

Cat::~Cat(void)
{
	std::cout << "Default Cat destructor" << std::endl;
}

Cat &	Cat::operator=(Cat const & rhs)
{
	std::cout << "Cat operator overload = called" << std::endl;
	this->_type = rhs._type;
	return (*this);
}

void	Cat::makeSound(void) const
{
	std::cout << "Miawwww" << std::endl;
}

std::string	Cat::getType(void) const
{
	return (this->_type);
}
