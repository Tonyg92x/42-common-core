/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classBrain.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:49:48 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 14:46:12 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBrain.hpp"

Brain::Brain(void)
{
	this->init_ideas();
	std::cout << "Default Brain constructor called" << std::endl;
}

Brain::Brain(Brain const &rhs)
{
	*this = rhs;
	std::cout << "Copy Brain contructor called" << std::endl;
}

Brain::~Brain(void)
{
	std::cout << "Default Brain destructor called" << std::endl;
}

Brain & Brain::operator=(Brain const &rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 100; i++)
			set_idea(i, rhs.get_idea(i));
	}
	return (*this);
}

void	Brain::init_ideas(void)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "An idea";
}

std::string	Brain::get_idea(size_t index) const
{
	if (index < 100)
		return (this->ideas[index]);
	return ("Out of Brain memory address");
}

void	Brain::set_idea(size_t index, std::string	lidea)
{
	this->ideas[index] = lidea;
}