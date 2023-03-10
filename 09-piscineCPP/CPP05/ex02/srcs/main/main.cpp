/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 10:40:38 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBureaucrat.hpp"
#include "classShrubberyCreationForm.hpp"
#include "classRobotomyRequestForm.hpp"
#include "classPresidentialPardonForm.hpp"

int	main(void)
{

    //  Shruberry Test's

    std::cout << "\033[32m\nTest for ShrybberyCreationForm\033[0m\n" << std::endl;
    try
    {
        ShrubberyCreationForm ShrubbForm("Jardin");
        Bureaucrat  Bob("Bob", 1);
        Bureaucrat  Clem("Clem", 150);
        Bureaucrat  Charles("Charles", 144);
        ShrubberyCreationForm ShrubbForm2("Jardin2");

        std::cout << "\033[32m\nGrade ok test\033[0m\n" << std::endl;
        std::cout << Bob << "\n" << ShrubbForm << std::endl;
        try
        {
           Bob.executeForm(ShrubbForm);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        try
        {
            Bob.signForm(ShrubbForm);
            Bob.executeForm(ShrubbForm);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "\033[32m\nGrade not ok test\033[0m\n" << std::endl;
        std::cout << Clem << "\n" << ShrubbForm << std::endl;
        try
        {
            Clem.signForm(ShrubbForm2);
            Clem.executeForm(ShrubbForm2);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << Charles << "\n" << ShrubbForm << std::endl;
        try
        {
            Charles.signForm(ShrubbForm2);
            Charles.executeForm(ShrubbForm2);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

//  Robotomy test's

    std::cout << "\033[32m\nTest for RobotomyRequestForm\033[0m\n" << std::endl;
    try
    {
        RobotomyRequestForm RB("Roboto");
        Bureaucrat  Bob("Bob", 1);
        Bureaucrat  Clem("Clem", 73);
        Bureaucrat  Charles("Charles", 46);
        RobotomyRequestForm RB2("Roboto2");

        std::cout << "\033[32m\nGrade ok test\033[0m\n" << std::endl;
        std::cout << Bob << "\n" << RB << std::endl;
        try
        {
           Bob.executeForm(RB);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        try
        {
            Bob.signForm(RB);
            Bob.executeForm(RB);
            Bob.executeForm(RB);
            Bob.executeForm(RB);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "\033[32m\nGrade not ok test\033[0m\n" << std::endl;
        std::cout << Clem << "\n" << RB2 << std::endl;
        try
        {
            Clem.signForm(RB2);
            Clem.executeForm(RB2);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << Charles << "\n" << RB2 << std::endl;
        try
        {
            Charles.signForm(RB2);
            Charles.executeForm(RB2);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    //  PresidentialForm test's


    std::cout << "\033[32m\nTest for PresidentialPardonForm\033[0m\n" << std::endl;
    try
    {
        PresidentialPardonForm RB("Evaluateur");
        Bureaucrat  Bob("Bob", 1);
        Bureaucrat  Clem("Clem", 26);
        Bureaucrat  Charles("Charles", 3);
        PresidentialPardonForm RB2("Evaluateur2");

        std::cout << "\033[32m\nGrade ok test\033[0m\n" << std::endl;
        std::cout << Bob << "\n" << RB << std::endl;
        try
        {
           Bob.executeForm(RB);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        try
        {
            Bob.signForm(RB);
            Bob.executeForm(RB);
            Bob.executeForm(RB);
            Bob.executeForm(RB);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "\033[32m\nGrade not ok test\033[0m\n" << std::endl;
        std::cout << Clem << "\n" << RB2 << std::endl;
        try
        {
            Clem.signForm(RB2);
            Clem.executeForm(RB2);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << Charles << "\n" << RB2 << std::endl;
        try
        {
            Charles.signForm(RB2);
            Charles.executeForm(RB2);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
	return (0);
}
