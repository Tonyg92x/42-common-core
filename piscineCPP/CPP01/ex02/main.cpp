/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 11:00:44 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int	main(void)
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	*stringPTR = &str;
	std::string &stringREF = str;

	//	Print memory adress

	std::cout << "str adress = \t\t" << &str << std::endl;
	std::cout << "stringPTR adress = \t" << stringPTR << std::endl;
	std::cout << "stringREF adress = \t" << &stringREF << std::endl;

	std::cout << "\n\n";

	//	Print content
	std::cout << "str content = \t\t" << str << std::endl;
	std::cout << "stringPTR content = \t" << (*stringPTR) << std::endl;
	std::cout << "stringREF content = \t" << stringREF << std::endl;

	return (0);
}