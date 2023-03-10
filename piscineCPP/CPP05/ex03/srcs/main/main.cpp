/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 13:06:21 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBureaucrat.hpp"
#include "classShrubberyCreationForm.hpp"
#include "classRobotomyRequestForm.hpp"
#include "classPresidentialPardonForm.hpp"
#include "classIntern.hpp"

int	main(void)
{
	Intern	someRandomIntern;
	AForm	*form = someRandomIntern.MakeForm("robot form", "bob");
    AForm	*form1 = someRandomIntern.MakeForm("shrubb form", "Jardin");
    AForm	*form2 = someRandomIntern.MakeForm("presidential form", "Evaluateur");

    if (form)
    {
        std::cout << *form << std::endl;
        delete form;
    }
    if (form1)
    {
        std::cout << *form1 << std::endl;
        delete form1;
    }
    if (form2)
    {
        std::cout << *form2 << std::endl;
        delete form2;
    }
}
