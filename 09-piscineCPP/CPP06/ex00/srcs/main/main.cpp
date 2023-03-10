/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 15:52:22 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classConverter.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "The program need one argument. \033[31mError:\033[0m 0"
			<< std::endl;
		return (1);
	}

    //  Get the string in the converter object
	Converter	i(argv[1]);

	//  Print value to char
    try
    {
        std::cout << "char: " << i.toChar() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;;
    }
	

	//	Print value to int
    try
    {
        std::cout << "int: " << i.toInt() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

	//	Print value to float
    try
    {
        if (i.getType() == "int" || i.getType() == "char")
            std::cout << "float: " << i.toFloat() << ".0f" << std::endl;
        else
            std::cout << "float: " << i.toFloat() << "f" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

	//	Print value to double
    try
    {
        if (i.getType() == "int" || i.getType() == "char")
            std::cout << "float: " << i.toFloat() << ".0" << std::endl;
        else
            std::cout << "double: " << i.toDouble() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

	return (0);
}
