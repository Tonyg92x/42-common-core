/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 09:28:10 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBureaucrat.hpp"
#include "classForm.hpp"

int	main(void)
{
    //  Working test

    std::cout << "\n\033[32mWorking test with default constructor's :\n\033[0m" << std::endl;
	try
	{
		Bureaucrat Bob("Bob", 1);
		AForm PermisChasse;
        std::cout << Bob << "\n" << PermisChasse;
        Bob.signForm(PermisChasse);
        std::cout << PermisChasse << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

   std::cout << "\n\033[32mForm grade to high on constructor test\n\033[0m" << std::endl;
   try
   {
        AForm PermisChasse("Permis de chasse", 1, -1);
   }
   catch(const std::exception& e)
   {
     std::cerr << e.what() << '\n';
   }

    std::cout << "\n\033[32mForm grade to high to sign\n\033[0m" << std::endl;
    try
    {
        Bureaucrat B;
        AForm F;
        std::cout << B << "\n" << F << std::endl;
        B.signForm(F);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\n\033[32mTest with assignation construtor's\n\033[0m" << std::endl;
    try
    {
        Bureaucrat  Bob("Bob", 15);
        AForm        PermisChasse("Permis de chasse", 50, 100);
        Bureaucrat  BobCopy(Bob);
        AForm        PermisChasseCopy(PermisChasse);

        std::cout << Bob << " == " << BobCopy << std::endl;
        std::cout << PermisChasse << " == " << PermisChasseCopy << std::endl;
        Bob.signForm(PermisChasse);
        Bob.signForm(PermisChasse);
        Bob.signForm(PermisChasseCopy);
        Bob.signForm(PermisChasseCopy);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
	return (0);
}
