/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classWrongCat.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:39:58 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 13:53:35 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "classWrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal("WrongCat")
{
	std::cout << "Default WrongCat constructor called" << std::endl;
	this->_type = "WrongCat";
}

WrongCat::WrongCat(WrongCat const & rhs) : WrongAnimal("WrongCat")
{
	std::cout << "Copy WrongCat constructor called" << std::endl;
	*this = rhs;
}

WrongCat::~WrongCat(void)
{
	std::cout << "Default WrongCat destructor" << std::endl;
}

WrongCat &	WrongCat::operator=(WrongCat const & rhs)
{
	std::cout << "WrongCat operator overload = called" << std::endl;
	this->_type = rhs._type;
	return (*this);
}

void	WrongCat::makeSound(void) const
{
	std::cout << "Miawwww" << std::endl;
}

std::string	WrongCat::getType(void) const
{
	return (this->_type);
}
