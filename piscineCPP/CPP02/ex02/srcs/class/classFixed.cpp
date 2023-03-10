/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFixed.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:07:28 by aguay             #+#    #+#             */
/*   Updated: 2022/06/28 15:59:00 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classFixed.hpp"
#include <cmath>

//	Contructor

Fixed::Fixed(void) : _rawBits(0){}

Fixed::Fixed(Fixed const & src){*this = src;}

Fixed::Fixed(int const entier)
{
	setRawBits(entier << bitFract);
}

Fixed::Fixed(float const nbVirgule)
{
	//	roundf(Float * 256)
	setRawBits((int)roundf(nbVirgule * (float)(1 << bitFract)));
}

//	Destructor
Fixed::~Fixed(void){}

//	Assignation operator overload

Fixed & Fixed::operator=(Fixed const & rhs)
{
	if (&rhs != this)
		_rawBits = rhs.getRawBits();

	return *this;
}

//	Arithmetic Operator overload
Fixed	Fixed::operator+(Fixed const & rhs) const
{
	return (Fixed(Fixed::toFloat() + rhs.toFloat()));
}

Fixed	Fixed::operator-(Fixed const &rhs) const
{
	return (Fixed(Fixed::toFloat() - rhs.toFloat()));
}

Fixed	Fixed::operator*(Fixed const &rhs) const
{
	return (Fixed(Fixed::toFloat() * rhs.toFloat()));
}

Fixed	Fixed::operator/(Fixed const &rhs) const
{
	return (Fixed(Fixed::toFloat() / rhs.toFloat()));
}

//	Boolean Algebra Operator overload

bool	Fixed::operator>(Fixed const &rhs) const
{
	return (Fixed::toFloat() > rhs.toFloat());
}

bool	Fixed::operator>=(Fixed const &rhs) const
{
	return (Fixed::toFloat() >= rhs.toFloat());
}

bool	Fixed::operator<(Fixed const &rhs) const
{
	return (Fixed::toFloat() < rhs.toFloat());
}

bool	Fixed::operator<=(Fixed const &rhs) const
{
	return (Fixed::toFloat() <= rhs.toFloat());
}

bool	Fixed::operator==(Fixed const &rhs) const
{
	return (Fixed::toFloat() == rhs.toFloat());
}

bool	Fixed::operator!=(Fixed const &rhs) const
{
	return (Fixed::toFloat() != rhs.toFloat());
}

//	Member fonctions
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

//	Fonction non member

Fixed &	Fixed::min(Fixed const &fixA, Fixed const &fixB)
{
	const Fixed	*ptr;

	if (fixA < fixB)
		ptr = &fixA;
	else
		ptr = &fixB;
	return (Fixed &)(*ptr);
}

Fixed &	Fixed::min(Fixed &fixA, Fixed &fixB)
{
	if (fixA < fixB)
		return (fixA);
	else
		return (fixB);
}

Fixed &	Fixed::max(Fixed const &fixA, Fixed const &fixB)
{
	const Fixed	*ptr;

	if (fixA > fixB)
		ptr = &fixA;
	else
		ptr = &fixB;
	return (Fixed &)(*ptr);
}

Fixed &	Fixed::max(Fixed &fixA, Fixed &fixB)
{
	if (fixA > fixB)
		return (fixA);
	else
		return (fixB);
}

//	Prefix, postfix incrementation/decrementation

Fixed &	Fixed::operator++()
{
	++_rawBits;

	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	temp(*this);

	this->_rawBits++;

	return (temp);
}

Fixed &	Fixed::operator--()
{
	--_rawBits;

	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	temp(*this);

	this->_rawBits--;

	return (temp);
}

std::ostream &	operator<<(std::ostream & o, Fixed const & rhs)
{
	o << rhs.toFloat();
	return (o);
}
