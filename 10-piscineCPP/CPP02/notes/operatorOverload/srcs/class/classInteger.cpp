/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classInteger.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:31:37 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 16:17:00 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classInteger.hpp"

Integer::Integer(int const n) : _n(n)
{
	std::cout << "Constructor called." << std::endl;
	return ;
}

Integer::~Integer(void)
{
	std::cout << "Destructor called." << std::endl;
	return ;
}

int Integer::getValue(void) const
{
	return (this->_n);
}

Integer &	Integer::operator=(Integer const & rhs)
{
	std::cout << "Assignation operator called from " << this->_n;
	std::cout << " to " << rhs.getValue() << std::endl;

	this->_n = rhs.getValue();

	return *this;
}

Integer Integer::operator+(Integer const & rhs) const
{
	std::cout << "Addition operator called with " << this->_n;
	std::cout << " and " << rhs.getValue() << std::endl;

	return Integer(this->_n + rhs.getValue());
}

std::ostream &	operator<<(std::ostream & o, Integer const &rhs)
{
	o << rhs.getValue();
	return o;
}
