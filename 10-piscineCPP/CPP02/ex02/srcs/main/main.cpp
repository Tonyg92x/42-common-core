/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/28 13:38:32 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classFixed.hpp"
#include <iostream>

int	main(void)
{
	Fixed	x((float)6.1);
	Fixed	y(5);

	// //	My own tests
	// std::cout << "x = " << x << " y = " << y << std::endl;

	// //	Boolean overload tests
	// std::cout << "\nBoolean algebra overload tests\n" << std::endl;
	// if (x < y)
	// 	std::cout << "x is smaller then y" << std::endl;
	// else
	// 	std::cout << "x is not smaller then y" << std::endl;
	// if (x <= y)
	// 	std::cout << "x is smaller or equal then y" << std::endl;
	// else
	// 	std::cout << "x is not smaller or equal then y" << std::endl;
	// if (x > y)
	// 	std::cout << "x is bigger then y" << std::endl;
	// else
	// 	std::cout << "x is not bigger then y" << std::endl;
	// if (x >= y)
	// 	std::cout << "x is bigger or equal then y" << std::endl;
	// else
	// 	std::cout << "x is not bigger or equal then y" << std::endl;
	// if (x == y)
	// 	std::cout << "x is equal to y" << std::endl;
	// else
	// 	std::cout << "x is not equal to y" << std::endl;
	// if (x != y)
	// 	std::cout << "x is not equal to y" << std::endl;
	// else
	// 	std::cout << "x is equal to y" << std::endl;

	// //	Aritmetic Operator overload
	// std::cout << x + y << std::endl;
	// std::cout << x - y << std::endl;
	// std::cout << x * y << std::endl;
	// std::cout << x / y << std::endl;
	
	//	PDF tests
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	return 0;
}