/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/09/30 14:41:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBureaucrat.hpp"

int	main(void)
{
	//	Trying to create a default constructor (ask user input)
	std::cout << "\n\033[32mTest with default constructor\033[0m\n" << std::endl;
	try
	{
		Bureaucrat	B0;
		std::cout << B0 << std::endl;
		std::cout << "\n\033[32mTest Bur.getGrade / Bur.getName\033[0m\n" << std::endl;
		std::cout << B0.getGrade() << " " << B0.getName() << std::endl;
		std::cout << "\n\033[32mTest decrem the lowest grade\033[0m\n" << std::endl;
		B0.decremGrade();
		std::cout << B0 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << '\n';
	}

	std::cout << "\n\033[32mTest with valid grade\033[0m\n" << std::endl;
	//	Try to create a Bureaucrate with valid info
	try
	{
		Bureaucrat	B1("Clem", 1);
		std::cout << B1 << std::endl;
		std::cout << "\n\033[32mTest copy constructor\033[0m\n" << std::endl;
		Bureaucrat	B4 = B1;
		std::cout << B4 << std::endl;
		std::cout << "\n\033[32mTest Bur.getGrade / Bur.getName\033[0m\n" << std::endl;
		std::cout << B4.getGrade() << " " << B4.getName() << std::endl;
		std::cout << "\n\033[32mTest increment highest grade\033[0m\n" << std::endl;
		B4.incremGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << '\n';
	}

	std::cout << "\n\033[32mTest with invalid grade (-1 then 151)\033[0m\n" << std::endl;
	//	Trying ot create a Bureaucrate with invalid ID
	try
	{
		Bureaucrat	B2("BOUAHAHAHAHHA", -1);
		std::cout << B2 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << '\n';
	}

	try
	{
		Bureaucrat	B3("R2D2", 151);
		std::cout << B3 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << '\n';
	}
	return (0);
}
