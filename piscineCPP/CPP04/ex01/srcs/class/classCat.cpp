/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:16:45 by aguay             #+#    #+#             */
/*   Updated: 2022/09/29 09:00:21 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classCat.hpp"

Cat::Cat(void) : AAnimal(), brain(new Brain)
{
	std::cout << "Default Cat constructor called" << std::endl;
	this->_type = "Cat";
}

Cat::Cat(Cat const & rhs) : AAnimal(), brain(new Brain)
{
	std::cout << "Copy Cat constructor called" << std::endl;
	*this = rhs;
}

Cat::~Cat(void)
{
	delete this->brain;
	std::cout << "Default Cat destructor" << std::endl;
}

Cat &	Cat::operator=(Cat const & rhs)
{
	std::cout << "Cat operator overload = called" << std::endl;
	if (this != &rhs)
		this->brain = rhs.brain;
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

void	Cat::get_idea(size_t index)
{
	std::cout << this->brain->get_idea(index) << std::endl;
}
