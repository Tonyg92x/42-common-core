/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 13:17:38 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classHarl.hpp"

int	main(void)
{
	Harl	karenBro;

	std::cout << "Test debug alone" << std::endl;
	karenBro.complain("DEBUG");

	std::cout << std::endl;
	
	std::cout << "Test info alone" << std::endl;
	karenBro.complain("INFO");

	std::cout << std::endl;

	std::cout << "Test warning alone" << std::endl;
	karenBro.complain("WARNING");

	std::cout << std::endl;

	std::cout << "Test error alone" << std::endl;
	karenBro.complain("ERROR");

	std::cout << std::endl;

	std::cout << "Test all backward" << std::endl;
	karenBro.complain("ERROR");
	karenBro.complain("WARNING");
	karenBro.complain("INFO");
	karenBro.complain("DEBUG");

	std::cout << std::endl;

	std::cout << "Test all in order" << std::endl;
	karenBro.complain("DEBUG");
	karenBro.complain("INFO");
	karenBro.complain("WARNING");
	karenBro.complain("ERROR");
	return (0);
}