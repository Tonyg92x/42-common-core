/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/17 12:32:14 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Array.hpp"

int	main(void)
{
	Array<int>      a;
    Array<float>    b(12);

    std::cout << "Float array test\n" << std::endl;
    {
        try
        {
            b[0] = 12.3f;
            std::cout << b[0] << std::endl;
            b[13] = 5.4f;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error : " << e.what() << std::endl;
        }
    }

    std::cout << "\nstring array test\n" << std::endl;
    {
        try
        {
            Array<std::string>  str(4);
            str[0] = "yo ca va ?";
            str[1] = "\n yeah mon garssss top shape";
            std::cout << str[0] << str[1] << std::endl;
            str[5] = "allo";
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error : " << e.what() << std::endl;
        }
    }

    std::cout << "\ncopy constuctor test\n" << std::endl;
    {
        try
        {
            Array<std::string> a(3);
            a[0] = "salut ca va";
            a[2] = "\nTom : oui toi ?";
            std::cout << a[0] << a[1] << a[2] << std::endl;
            Array<std::string> b = a;
            std::cout << b[0] << b[1] << b[2] << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error : " << e.what() << std::endl;
        }
    }
	return (0);
}
