/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classSample.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:10:22 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 14:22:40 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classSample.hpp"
#include <iostream>

Sample::Sample(void)
{
	std::cout << "Constructor called." << std::endl;
	return ;
}

Sample::~Sample(void)
{
	std::cout << "Destructor called." << std::endl;
	return ;
}

void	Sample::bar(char const c) const
{
	std::cout << "Member function called with char overload : " << c << std::endl;
	return ;
}

void	Sample::bar(int const n) const
{
	std::cout << "Member function called with int overload : " << n << std::endl;
	return ;
}

void	Sample::bar(float const z) const
{
	std::cout << "Member function called with flot overload : " << z << std::endl;
	return ;
}

void	Sample::bar(Sample const & i) const
{
	(void)i;
	std::cout << "Member function called with Sample overload : " << std::endl;
	return ;
}
