/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFixed.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:28 by aguay             #+#    #+#             */
/*   Updated: 2022/06/27 11:25:03 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classFixed.hpp"

Fixed::Fixed(void)
{
	std::cout << "Default constructor called" << std::endl;
	Fixed::setRawBits(0);
	return ;
}

Fixed::Fixed(Fixed const & src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;

	return ;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
	return ;
}

Fixed & Fixed::operator=(Fixed const & rhs)
{
	std::cout << "Operator overload assignation called" << std::endl;
	Fixed::setRawBits(rhs.getRawBits());

	return *this;
}

void	Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
	return ;
}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member fonction called" << std::endl;
	return (this->_rawBits);
}
