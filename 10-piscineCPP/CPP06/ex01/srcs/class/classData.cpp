/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:35:03 by aguay             #+#    #+#             */
/*   Updated: 2022/10/10 13:24:47 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classData.hpp"

//  Constructor's

Data::Data(void) : _ptr(&(*this)){}

Data::Data(Data const &rhs) : _ptr(&(*this)){*this = rhs;}

//  Destructor's

Data::~Data(){}

//  Operation overload

Data &  Data::operator=(Data const & rhs)
{
    (void) rhs;
    return (*this);
}

const void  *Data::get_ptr(void)
{
    return (this->_ptr);
}
