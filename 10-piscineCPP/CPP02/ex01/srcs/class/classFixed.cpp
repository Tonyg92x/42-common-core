/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFixed.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:28 by aguay             #+#    #+#             */
/*   Updated: 2022/06/28 10:07:16 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classFixed.hpp"
#include <cmath>

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

Fixed::Fixed(int const entier)
{
	std::cout << "Int constructor called" << std::endl;
	setRawBits(entier << bitFract);
}

Fixed::Fixed(float const nbVirgule)
{
	//	roundf(Float * 256)
	setRawBits((int)roundf(nbVirgule * (float)(1 << bitFract)));
	std::cout << "Float constructor called" << std::endl;
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
	return (this->_rawBits);
}

float	Fixed::toFloat(void) const
{
	return ((float)Fixed::getRawBits() / (1 << bitFract));
}

int	Fixed::toInt(void) const
{
	return (Fixed::getRawBits() >> bitFract);
}

std::ostream &	operator<<(std::ostream & o, Fixed const & rhs)
{
	o << rhs.toFloat();
	return (o);
}